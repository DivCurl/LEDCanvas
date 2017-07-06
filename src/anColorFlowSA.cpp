#include "./include/anColorFlowSA.h" 

extern int16c sampleBuffer[ N ]; //initialize buffer to collect samples
extern volatile int sampleIndex;
extern int analyzerRun;
extern int16c din[ N ];       // buffer to hold old samples
extern int16c dout[ N ];      // holds computed FFT
extern int16c scratch[ N ];
extern int16c twiddle [ N / 2 ];
extern short singleSidedFFT[ N ];
extern long maxM;
extern int log2N; // log2(128) = 7

anColorFlowSA::anColorFlowSA( npDisplay* pDisplay, int frames, int id, mode_t mode ) 
 : npAnimation( pDisplay, frames, id, mode ) { }

anColorFlowSA::~anColorFlowSA( void ) { }

int anColorFlowSA::Draw() {    
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
            
            ComputeFFT();     
            
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

int anColorFlowSA::Init() {
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