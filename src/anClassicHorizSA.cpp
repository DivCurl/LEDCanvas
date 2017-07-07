#include "./include/anClassicHorizSA.h" 

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

anClassicHorizSA::anClassicHorizSA( npDisplay* pDisplay, mode_t mode, int frames, opt_t opts ) 
 : npAnimation( pDisplay, mode, frames, opts ) { }

anClassicHorizSA::~anClassicHorizSA( void ) { }

int anClassicHorizSA::Draw() {    
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
            int barLength = 0;
            int ii = 0;
            ComputeFFT();
            
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
                
                if ( i % 2 == 0 ) {  // alternate bottom/top columns on even/odd values of i
                     SetCol( ii, GetRowBottom(), barLength, rgbwGetByAngle( angle + ( i * 20 )  ) ); 
                } else {
                    SetCol( ii, 59, 59 - barLength, rgbwGetByAngle( angle + 180 + ( i * 20 ) ) );    
                    ii++;
                }             
                barLength = 0; // reset for next run through loop
            }

            if ( ( angle += 0.1 ) > 360 ) { 
               angle -= 360 ;
            }
            
            framesDrawn++;
        }      
        RefreshDisplay();
    }   // end loop
    
    analyzerRun = 0;
    return ( ret );   // return 0 when all animations done
}

int anClassicHorizSA::Init() {
    firstScan = 1;
    framesDrawn = 0;
    skip = 0;
    ret = MODE_NONE;
    Clr();    
    memcpy( twiddle, fftc, sizeof( twiddle ) ); // copy twiddle factors from flash to RAM  
    analyzerRun = 1;    // used by T4 ISR
    newSample = 0;
    sampleIndex = 0;
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
    
    return ( 0 );
}