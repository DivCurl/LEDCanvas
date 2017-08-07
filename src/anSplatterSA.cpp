#include "./include/anSplatterSA.h" 

// Refer to fft.h/fft.cpp
extern bool analyzerRun;
extern volatile bool FFTBufferReady;
extern short singleSidedFFT[ N ];

anSplatterSA::anSplatterSA( npDisplay* pDisplay, mode_t mode, int frames, opt_t opts, scale_t customScaling ) 
 : npAnimation( pDisplay, mode, frames, opts, customScaling ) {
    // Sync current animation runtime mode settings to LCD display
    if ( modeFlags.test( MODE_REPEAT ) ) {
        LCDSendMessage( LCD_SET_REPEAT_ON, 6 );   
    } else {
        LCDSendMessage( LCD_SET_REPEAT_OFF, 6 );   
    }
    
    analyzerRun = 1;    // used by T4 ISR
    InitFFT();
}

anSplatterSA::~anSplatterSA() {
    analyzerRun = 0;
}

int anSplatterSA::Draw() {    
    // Main animation loop
    counter fadeCtr ( 20, ON );
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
            int numSplats;
            
            if ( FFTBufferReady ) {
                ComputeFFT();                
            }  
           
            if ( fadeCtr.Done() ) {
                fadeCtr.Reset();
                FadeOut();                      
            }            

            for ( int i = 0; i <= GetColRight(); i++ ) {        // loop across x (frequency) axis, bottom half       
                // Get number of splats for this column
                numSplats = (int)round( Remap ( singleSidedFFT[ i * 6 ], -60, -10, 0, 8 ) ) ;
                
                if ( numSplats > 0 ) {
                    // randomize where they go and draw them
                    for ( int j = 0; j <= numSplats; j++ ) {
                        int rnd = rand() % 60;
                        Set( i, rnd, rgbwGetByAngle( rand() % 360, rand() % 32 ) );
                    }
                }
            }
            
            framesDrawn++;
        }      
        RefreshDisplay();
    }   // end main loop
    
    return ( MODE_NEXT );
}
