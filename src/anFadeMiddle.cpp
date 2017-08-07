#include "./include/anFadeMiddle.h"

using namespace std;

anFadeMiddle::anFadeMiddle( npDisplay* pDisplay, mode_t mode, int frames, opt_t opts, scale_t customScaling ) 
: npAnimation( pDisplay, mode, frames, opts, customScaling ) {
    // Sync current animation runtime mode settings to LCD display
    if ( modeFlags.test( MODE_REPEAT ) ) {
        LCDSendMessage( LCD_SET_REPEAT_ON, 6 );   
    } else {
        LCDSendMessage( LCD_SET_REPEAT_OFF, 6 );   
    }
}

anFadeMiddle::~anFadeMiddle() { }

int anFadeMiddle::Draw() {
    angle = 0.f;
    StartDelayCounter( 40 ); 
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
            if ( ctrDelay.Done() ) {    
                ctrDelay.Reset();  
                
                if ( angle < 360 ) {            
                    for ( int i = 0; i <= GetColRight(); i++ ) {
                        for ( int j = 30, jj = 1; j <= 59; j++, jj++ ) {
                            // Fade top to center with decreasing brightness
                            Set( i, j, rgbwGetByAngle( angle + (i*40) + (j*7)), jj*8.8 ); 
                        }
                        
                        for ( int j = 29, jj = 1; j >= 0; j--, jj++ ) {
                            // Fade bottom to center with decreasing brightness
                            Set( i, j, rgbwGetByAngle( angle + (i*40) + (j*7)), jj*8.8 ); 
                        }
                    }
                } else {
                    angle -= 360;
                }

                angle += 2;                
                framesDrawn++;
            }                               
        }
        
        RefreshDisplay();
    } // end main loop          
    
    return ( MODE_NEXT );
}
