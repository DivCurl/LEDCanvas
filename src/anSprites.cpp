#include "./include/anSprites.h"

using namespace std;

anSprites::anSprites( npDisplay* pDisplay, mode_t mode, int frames, opt_t opts ) 
: npAnimation( pDisplay, mode, frames, opts ) {
    // Sync current animation runtime mode settings to LCD display
    if ( modeFlags.test( MODE_REPEAT ) ) {
        LCDSendMessage( LCD_SET_REPEAT_ON, 6 );   
    } else {
        LCDSendMessage( LCD_SET_REPEAT_OFF, 6 );   
    }  
}

anSprites::~anSprites() { }

int anSprites::Draw() {
    vector<pixel> pixels( 10 );
    // Main animation loop
    vector<pixel>::iterator it;
    int i;
    
    // Testing
    // Generate pixels
    for ( i = 0, it = pixels.begin(); it < pixels.end(); it++, i++ ) {
        (*it).coord.x = 0;
        (*it).coord.y = i;
        (*it).color = rgbwGetByAngle( 0 );
    }
    
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
                StartDelayCounter( 1000 );       
            }  
            
           if ( ctrDelay.Update() ) { 
               ctrDelay.Reset(); 
               Clr();
               
               // Decrease one-by-one
               if ( !pixels.empty() ) {
                   pixels.pop_back();
               }
               
               Blit( pixels );    
           }
           
            RefreshDisplay();        
        }
    } // end main loop
    
    return ( ret );
}