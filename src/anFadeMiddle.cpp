#include "./include/anFadeMiddle.h"

using namespace std;

anFadeMiddle::anFadeMiddle( npDisplay* pDisplay, mode_t mode, int frames, opt_t opts ) 
: npAnimation( pDisplay, mode, frames, opts ) { }

int anFadeMiddle::Draw() {
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
           if ( firstScan ) {
            firstScan = 0;
            angle = 0.f;
            StartDelayCounter( 40 ); 
            ctrDelay.Reset();
            }
    
            if ( ctrDelay.Update() ) {    
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
                ctrDelay.Reset();  

                framesDrawn++;
            }                               
        }
        
        RefreshDisplay();
    } // end while loop         
    
    return ( ret );
}

int anFadeMiddle::Init() {   
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