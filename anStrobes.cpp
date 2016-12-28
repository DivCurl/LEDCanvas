#include "anStrobes.h"

anStrobes::anStrobes( npDisplay* pDisplay, int frames, int id, mode_t mode ) 
: npAnimation( pDisplay, frames, id, mode ) {
}

anStrobes::~anStrobes() {    
    
}

int anStrobes::Draw() {
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
            switch ( id ) {
                case ID_STROBE_BASIC:
                    if ( StrobeBasic() ) {
                        framesDrawn++;
                    }
                    break;
                    
                case ID_STROBE_CHASER:
                    if ( StrobeChaser() ) {
                        framesDrawn++;
                    }
                    break;

                default:
                    break;
            }
        }
        RefreshDisplay();
    } // end while loop         
    
    return ( ret );
}

int anStrobes::Init() {   
    firstScan = 1;    
    framesDrawn = 0;    
    skip = 0;
    ret = MODE_NONE;
    Clr();
}

bool anStrobes::StrobeBasic() {    
    if ( firstScan ) {
        angle = rand() % 360;
        firstScan = 0;
        StartDelayCounter( strobeRate );      // 10 fastest, 80 slowest   
        ctrDelay.Reset();
    }
    
    if ( ctrDelay.Update() ) {    
        if ( framesDrawn % 2 ) { // blank display every other frame
            Clr();
        } else {
            for ( int j = 0; j <= GetRowTop(); j++ ) {
                SetRow( j, rgbwGetByAngle( angle ), 80 );
            }
        }
        
        ctrDelay.Reset();
        return ( FRAME_DRAWN );
    }
            
    return ( FRAME_SKIP );
    
}

bool anStrobes::StrobeChaser() {
    
}


