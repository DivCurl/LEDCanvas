#include "./include/anColorFlowSA.h" 

// Refer to fft.h/fft.cpp
extern bool analyzerRun;
extern volatile bool FFTBufferReady;
extern short singleSidedFFT[ N ];

anColorFlowSA::anColorFlowSA( npDisplay* pDisplay, mode_t mode, int frames, opt_t opts, scale_t customScale ) 
 : npAnimation( pDisplay, mode, frames, opts, customScale ) {
     // Sync current animation runtime mode settings to LCD display
    if ( modeFlags.test( MODE_REPEAT ) ) {
        LCDSendMessage( LCD_SET_REPEAT_ON, 6 );   
    } else {
        LCDSendMessage( LCD_SET_REPEAT_OFF, 6 );   
    }
    
    analyzerRun = 1;    // used by T4 ISR
    InitFFT();
}

anColorFlowSA::~anColorFlowSA() {
    analyzerRun = 0;   // used by T4 ISR
}

int anColorFlowSA::Draw() {    
    StartDelayCounter( 25 );         
    
    // Main animation loop
    while ( ( framesDrawn < frames ) || modeFlags.test( MODE_REPEAT ) ) {
        if ( globalMode.msgPending ) { 
            PollGlobalModes();  // handle any new external I/O messages
        }
        
        if ( modeFlags.test( MODE_OFF ) ) {
            Clr();        
        }        
        
        if ( ret == MODE_PREV || ret == MODE_NEXT ) {
            return ( ret );  // break while loop and return to main signaling next/prev animation to be drawn
        }     
    
        if ( !skip ) { 
            int barLength;
            
            if ( FFTBufferReady ) {
                ComputeFFT();
            }   

            // Each update, check remaining column shifts. While there are some left, shift the column up.
            if ( ctrDelay.Done() ) {                
                ctrDelay.Reset();
                ShiftUp();
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
    } // end main loop   
    
    return ( MODE_NEXT );
}
