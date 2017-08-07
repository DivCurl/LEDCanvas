#include "./include/anPulseFadeSA.h" 

// Refer to fft.h/fft.cpp
extern bool analyzerRun;
extern volatile bool FFTBufferReady;
extern short singleSidedFFT[ N ];

anPulseFadeSA::anPulseFadeSA( npDisplay* pDisplay, mode_t mode, int frames, opt_t opts, scale_t customScaling ) 
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

anPulseFadeSA::~anPulseFadeSA() {
    analyzerRun = 0;
}

int anPulseFadeSA::Draw() {    
    StartDelayCounter( 50 );      
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

            if ( ctrDelay.Done() ) {
                ctrDelay.Reset();
                FadeOut();                
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
            
            framesDrawn++;
        }      
        
        RefreshDisplay();
    }   // end main loop
    
    return ( MODE_NEXT );
}
