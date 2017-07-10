#include "./include/anColorRaceSA.h" 

// Refer to fft.h/fft.cpp
extern int16c sampleBuffer[ N ];
extern volatile int sampleIndex;
extern bool analyzerRun;
extern volatile bool newSample;
extern int16c din[ N ];
extern int16c dout[ N ];
extern int16c scratch[ N ];
extern int16c twiddle [ N / 2 ];
extern short singleSidedFFT[ N ];
extern long maxM;
extern int log2N; 

anColorRaceSA::anColorRaceSA( npDisplay* pDisplay, mode_t mode, int frames, opt_t opts ) 
 : npAnimation( pDisplay, mode, frames, opts ) { 
    InitFFT();
}

anColorRaceSA::~anColorRaceSA( void ) { }

int anColorRaceSA::Draw() {    
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
            int barLength;
            static int remainingShifts[ 9 ];
            
            ComputeFFT();             
            
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
            
            framesDrawn++;
        }      
        RefreshDisplay();
    }   // end loop
    
    analyzerRun = 0;
    return ( ret );   // return 0 when all animations done
}

int anColorRaceSA::Init() {
    firstScan = 1;
    framesDrawn = 0;
    skip = 0;
    ret = MODE_NONE;
    Clr();    
    memcpy( twiddle, fftc, sizeof( twiddle ) ); // copy twiddle factors from flash to RAM  
    analyzerRun = 1;    // used by T4 ISR
    newSample = 0;
    // sampleIndex = 0;
    // memcpy( sampleBuffer, 0, sizeof( sampleBuffer ) );
    // memcpy( din, 0, sizeof( din ) );
    // memcpy( dout, 0, sizeof( dout ) );      
    
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