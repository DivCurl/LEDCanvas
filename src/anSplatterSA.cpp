#include "./include/anSplatterSA.h" 

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

anSplatterSA::anSplatterSA( npDisplay* pDisplay, mode_t mode, int frames, opt_t opts ) 
 : npAnimation( pDisplay, mode, frames, opts ) { }

anSplatterSA::~anSplatterSA( void ) { }

int anSplatterSA::Draw() {    
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
            int numSplats;
            ComputeFFT();              
    
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
            
            framesDrawn++;
        }      
        RefreshDisplay();
    }   // end loop
    
    analyzerRun = 0;
    return ( ret );   // return 0 when all animations done
}

int anSplatterSA::Init() {
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