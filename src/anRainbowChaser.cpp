#include "./include/anRainbowChaser.h"

using namespace std;

anRainbowChaser::anRainbowChaser( npDisplay* pDisplay, mode_t mode, int frames, opt_t opts ) 
: npAnimation( pDisplay, mode, frames, opts ) {
    // Sync current animation runtime mode settings to LCD display
    if ( modeFlags.test( MODE_REPEAT ) ) {
        LCDSendMessage( LCD_SET_REPEAT_ON, 6 );   
    } else {
        LCDSendMessage( LCD_SET_REPEAT_OFF, 6 );   
    }
}

anRainbowChaser::~anRainbowChaser() { }

int anRainbowChaser::Draw() {
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
            break;  // break while loop and return to main signaling next/prev animation to be drawn
        }   
        
        if ( !skip ) {              
            if ( ctrDelay.Done() ) {    
                ctrDelay.Reset();  
                
                if ( angle < 360 ) {            
                    for ( int i = 0; i <= GetColRight(); i++ ) {
                        for (int j = 0; j <= GetRowTop(); j++ ) {
                            if ( i % 2 == 0 ) {     // fade rainbow in opposite directions over alternating columns
                                Set ( i, j, rgbwGetByAngle( (j + angle) * 3, 0 ) ) ;
                            } else {
                                Set ( i, (GetRowTop() - j), rgbwGetByAngle( (j + angle) * 3, 0 ) ) ;
                            }
                        }
                    }
                } else {
                    angle = angle - 360;
                }

                angle += 5;                
                framesDrawn++;
            }        
        }
        
        RefreshDisplay();
    } // end main loop       
    
    return ( ret );
}
