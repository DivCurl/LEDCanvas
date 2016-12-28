#include "anAnalyzers.h" 

// global so ISR can access
int16c sampleBuffer[ N ]; //initialize buffer to collect samples
volatile int sampleIndex = 0;
int analyzerRun = 0;
int16c din[ N ];       // buffer to hold old samples
int16c dout[ N ];      // holds computed FFT
int16c scratch[ N ];
int16c twiddle [ N / 2 ];
short singleSidedFFT[ N ];
long maxM = 0;
int log2N = 7; // log2(128) = 7

anAnalyzers::anAnalyzers( npDisplay* pDisplay, int frames, int id, mode_t mode ) 
 : npAnimation( pDisplay, frames, id, mode ) {

}

anAnalyzers::~anAnalyzers( void ) {

}

int anAnalyzers::Draw() {    
    Init();
    
    // Main animation loop
    while ( ( framesDrawn < frames ) || modeFlags.test( MODE_REPEAT ) ) {
        if ( globalMode.msgPending ) { 
            PollGlobalModes();  // handle any new external I/O messages
        }                
        if ( modeFlags.test( MODE_OFF ) ) {
            Clr();
        }        
        if ( ret == MODE_PREV || ret == MODE_NEXT ) {
            break;  // break while loop and return to main signaling next/prev animation to be drawn
        }     
    
        if ( !skip ) { 
            switch ( id ) {
                case ID_ANALYZER_CLASSIC1:                
                    ComputeFFT();                   
                    if ( ClassicHoriz() ) {
                        framesDrawn++;
                    } 
                    break;

                case ID_ANALYZER_CLASSIC2:
                    ComputeFFT();                   
                    if ( ClassicHoriz2() ) {
                        framesDrawn++;
                    }
                    break;

                case ID_ANALYZER_SPLATTER:
                    ComputeFFT();
                    if ( Splatter() ) {
                        framesDrawn++;
                    }
                    break;

                case ID_ANALYZER_FADE:
                    ComputeFFT();
                    if ( PulseFade() ) {
                        framesDrawn++;
                    }
                    break;

                case ID_ANALYZER_COLOR_FLOW:
                    ComputeFFT();
                    if ( ColorFlow() ) {
                        framesDrawn++;
                    }
                    break;

                case ID_ANALYZER_RACECARS:
                    ComputeFFT();
                    if ( Racecars() ) {
                        framesDrawn++;
                    }
                    break;

                default:
                    break;
            }
        }      
        RefreshDisplay();
    }   // end loop
    
    analyzerRun = 0;
    return ( ret );   // return 0 when all animations done
}

int anAnalyzers::Init() {
    firstScan = 1;
    framesDrawn = 0;
    skip = 0;
    ret = MODE_NONE;
    Clr();    
    analyzerRun = 1;    // used by T4 ISR
    memcpy( twiddle, fftc, sizeof( twiddle ) ); // copy twiddle factors from flash to RAM      
    
    // Sync current animation runtime mode settings to LCD display
    if ( modeFlags.test( MODE_REPEAT ) ) {
        LCDSendMessage( LCD_SET_REPEAT_ON, 6 );   
    } else {
        LCDSendMessage( LCD_SET_REPEAT_OFF, 6 );   
    }
    
    if ( modeFlags.test( MODE_PAUSE ) ) {
        LCDSendMessage( LCD_SET_PAUSE_ON, 6 );   
    } else {
        LCDSendMessage( LCD_SET_PAUSE_OFF, 6 );   
    }
}

__attribute__ ( ( optimize( "unroll-loops" ) ) )
void anAnalyzers::ComputeFFT( ) {
    mT4IntEnable( 0 );
    for ( int i = 0; i < N; i++ ) {
        if ( i < sampleIndex ) {
            din[ i + ( N - sampleIndex ) ] = sampleBuffer[ i ];
        } else {
            din[ i - sampleIndex ] = sampleBuffer[ i ];
        }
    }  
    
    mips_fft16( dout, din, twiddle, scratch, log2N ); 
    
    for ( int i = 1; i < N / 2; i++ ) {     // skip [0] because it contains garbage
        float re_sqr = ( dout[ i ].re * dout[ i ].re );
        float im_sqr = ( dout[ i ].im * dout[ i ].im );
        /*
        float dB = (float)( sqrt( re_sqr + im_sqr ) * 2 ) / 1024;
        if ( dB < 0.002 ) {     
            dB = 0.002; // clamp to -54dB
        }
        
        singleSidedFFT[ i - 1 ] = 20 * log10( dB );	// calculate dB and store in final holding array
         */
        singleSidedFFT[ i - 1 ] = (short)dbLUT[ ( int) ( sqrt(re_sqr + im_sqr) ) ];     // scaled to dB using lookup table for speed
        // singleSidedFFT[ i - 1 ] = sqrt(re_sqr + im_sqr );    // linear amplitude
    }

    mT4IntEnable( 1 );
}

// Draws spectrum with x-coords corresponding to frequency bins
bool anAnalyzers::ClassicHoriz() {    
    int barLength = 0;
    if ( firstScan ) {
        firstScan = 0;
        StartDelayCounter( 10 );         
        ctrDelay.Reset();
        angle = 0;
        counters.resize( GetColRight() + 1 );
        peaks.resize( GetColRight() + 1 );
    }    
    if ( ctrDelay.Update() ) {
        ShiftDown();        
        ctrDelay.Reset();
    }
        
    for ( int i = 0; i <= GetColRight(); i++ ) {        // loop across x (frequency) axis, bottom half       
        // Update height
        for ( int j = 0; j < GetRowTop(); j++ ) {       // check values in FFT array for each row and update bar length accordingly
            if ( Remap ( singleSidedFFT[ i*2 + 3], -50, -dbGain, 0, 29 ) > j  ) {   // offset +1 because [0] element contains garbage]
                barLength = j;
            }
        }           
        
        if ( barLength > 0 ) {
            SetCol( i, 30, barLength, rgbwGetByAngle( angle + ( i * 20 )  ) ); 
                
        }
        barLength = 0;
    
    }
    
    // mirror across center       
    if ( ( angle += 0.1 ) > 360 ) { 
       angle -= 360 ;
    }
    
    return ( FRAME_DRAWN );
}

// Draws spectrum with x-coords corresponding to frequency bins
bool anAnalyzers::ClassicHoriz2() {   
    int barLength = 0;
    int ii = 0;
    if ( firstScan ) {
        firstScan = 0;
        angle = 0;
        StartDelayCounter( 12 );         
        ctrDelay.Reset();
    }            
    if ( ctrDelay.Update() ) {
        ShiftDown( 0, 29 );         // shift down the bottom half of the display
        ShiftUp( 30, 59 );          // shift up the upper half of the display
        ctrDelay.Reset();
    }
    
    for ( int i = 0; i < 18; i++ ) {   // loop across x (frequency) axis, lower & upper halves    
        // Update height
        for ( int j = 0; j <= 29; j++ ) {           
            if ( Remap ( singleSidedFFT[ i + 3 ], -50, -dbGain, 0, 29 ) > j ) {   
                barLength = j;
            }
            
        }           
       
        // if ( barLength > 0 ) {
            if ( i % 2 == 0 ) {  // alternate bottom/top columns on even/odd values of i
                 SetCol( ii, GetRowBottom(), barLength, rgbwGetByAngle( angle + ( i * 20 )  ) ); 
            } else {
                SetCol( ii, 59, 59 - barLength, rgbwGetByAngle( angle + 180 + ( i * 20 ) ) );    
                ii++;
            }             
            barLength = 0; // reset for next run through loop
        // }  
    }
    
    if ( ( angle += 0.1 ) > 360 ) { 
       angle -= 360 ;
    }
    
    return ( FRAME_DRAWN );   
}

bool anAnalyzers::PulseFade() {
    int barLength = 0;
    if ( firstScan ) {
        firstScan = 0;
        StartDelayCounter( 50 );         
        ctrDelay.Reset();
        angle = 0;
    }    
    
    if ( ctrDelay.Update() ) {
        FadeOut();
        ctrDelay.Reset();
    }
            
    for ( int i = 0; i <= GetColRight(); i++ ) {        // loop across x (frequency) axis, bottom half       
        // Update height
        for ( int j = 0; j < GetRowTop(); j++ ) {       // check values in FFT array for each row and update bar length accordingly
            if ( Remap ( singleSidedFFT[ i*2 + 3], -50, -dbGain, 0, 59 ) > j  ) {   // offset +1 because [0] element contains garbage]
                barLength = j;
            }
        }           
        
        if ( barLength > 0 ) {
            float brt = Remap( barLength, 0, 59, 128, 255 );            

            // draw with brightness a function of barlength
            SetCol( i, GetRowBottom(), barLength, rgbwGetByAngle( angle + ( i * 40, rand() % 32 ) ), brt );
        }
        barLength = 0;
    
    }        
    
    if ( ( angle += 3 ) > 360 ) { 
        angle -= 360 ;
    }
    
    return ( FRAME_DRAWN );
}

bool anAnalyzers::Splatter() {
    int numSplats;
    
    if ( firstScan ) {
        firstScan = 0;
        StartDelayCounter( 20 );         
        ctrDelay.Reset();
    }
    
    if ( ctrDelay.Update() ) {
        FadeOut();      
        ctrDelay.Reset();
    }
    
    for ( int i = 0; i <= GetColRight(); i++ ) {        // loop across x (frequency) axis, bottom half       
        // Get number of splats for this column
        for ( int j = 1; j <= 10; j++ ) {       // check values in FFT array for each row and update bar length accordingly
            if ( ( Remap ( singleSidedFFT[ ( i + 1 ) ], -45, -dbGain, 0, 10 ) > j ) ) {
                numSplats++;
            }
            
        }
        if ( numSplats > 0 ) {
            // randomize where they go and draw them
            for ( int j = 0; j <= numSplats; j++ ) {
                int rnd = rand() % 60;
                Set( i, rnd, rgbwGetByAngle( rand() % 360, rand() % 32 ) );
            }
        }
        
        numSplats = 0;    
    }        
    
    return ( FRAME_DRAWN );    
}
    
bool anAnalyzers::Racecars() {   
    int barLength;
    static int remainingShifts[ 9 ];
    if ( firstScan ) {
        firstScan = 0;
        StartDelayCounter( 25 ); 
        firstScan = 0;
        ctrDelay.Reset();
    }
    
    // Each update, check remaining column shifts. While there are some left, shift the column up.
    if ( ctrDelay.Update() ) {
        // ShiftUp();
        for ( int i = 0; i < 9; i++ ) {
            if ( remainingShifts[ i ] > 0 ) {
                ShiftColUp( i );
                remainingShifts[ i ]--;
            }
        }
        ctrDelay.Reset();
        
    }
    
    for ( int i = 0; i <= GetColRight(); i++ ) {   // loop across x (frequency) axis, lower & upper halves    
        // Update height
        for ( int j = 0; j <= 59; j++ ) {           
            if ( Remap ( singleSidedFFT[ i + 3 ], -50, -dbGain, 0, 15 ) > j ) {   
                barLength = j;
            }            
        }           
       
        if ( barLength > 0 /* && !remainingShifts [ i ] */ ) {        
            SetCol( i, GetRowBottom(), barLength, rgbwGetByAngle( angle + (i * 30 ), rand() % 16  ) ); 
            remainingShifts[ i ] = barLength;
        }
        barLength = 0;
    }
        
    if ( ( angle += 3 ) > 360 ) { 
        angle -= 360 ;
    }
}

bool anAnalyzers::ColorFlow() {   
    int barLength;
    // static int remainingShifts[ 9 ];
    if ( firstScan ) {
        firstScan = 0;
        StartDelayCounter( 25 );         
        ctrDelay.Reset();
    }
    
    // Each update, check remaining column shifts. While there are some left, shift the column up.
    if ( ctrDelay.Update() ) {
        ShiftUp();
        ctrDelay.Reset();
    }
    
    for ( int i = 0; i <= GetColRight(); i++ ) {   // loop across x (frequency) axis, lower & upper halves    
        // Update height
        for ( int j = 0; j <= 29; j++ ) {           
            if ( Remap ( singleSidedFFT[ i + 3 ], -50, -dbGain, 0, 48 ) > j ) {   
                barLength = j;
            }            
        }           
       
   
        SetCol( i, GetRowBottom(), barLength, rgbwGetByAngle( angle + ( i * 20 )  ) ); 
        // remainingShifts[ i ] = barLength;
   
        barLength = 0;
    }
    
    if ( ( angle += 3 ) > 360 ) { 
        angle -= 360 ;
    }   
}    
