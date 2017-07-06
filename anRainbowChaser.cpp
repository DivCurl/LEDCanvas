#include <stdio.h>
#include "anRainbowChaser.h"

using namespace std;

anRainbowChaser::anRainbowChaser( npDisplay* pDisplay, int frames, int id, mode_t mode ) 
: npAnimation( pDisplay, frames, id, mode ) {
    
}

anRainbowChaser::~anRainbowChaser() {    
    
}

int anRainbowChaser::Draw() {
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
            static float d = 0;
    
            if ( firstScan ) {
                firstScan = 0;
                StartDelayCounter( 40 );         
                ctrDelay.Reset();
            }

            if ( ctrDelay.Update() ) {    
                if ( d < 360 ) {            
                    for ( int i = 0; i <= GetColRight(); i++ ) {
                        for (int j = 0; j <= GetRowTop(); j++ ) {
                            if ( i % 2 == 0 ) {     // fade rainbow in opposite directions over alternating columns
                                Set ( i, j, rgbwGetByAngle( (j + d) * 3, 0 ) ) ;
                            } else {
                                Set ( i, (GetRowTop() - j), rgbwGetByAngle( (j + d) * 3, 0 ) ) ;
                            }
                        }
                    }
                } else {
                    d = d - 360;
                }

                d += 2;
                ctrDelay.Reset();  
                framesDrawn++;
            }        
        }
        
        RefreshDisplay();
    } // end while loop         
    
    return ( ret );
}

int anRainbowChaser::Init() {
    firstScan = 1;    
    framesDrawn = 0;    
    skip = 0;
    ret = MODE_NONE;
    Clr();
    
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