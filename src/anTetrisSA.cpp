#include "./include/anTetrisSA.h"

using namespace std;

anTetrisSA::anTetrisSA( npDisplay* pDisplay, mode_t mode, int frames, opt_t opts )
: npAnimation( pDisplay, mode, frames, opts ) {
    // Sync current animation runtime mode settings to LCD display
    if ( modeFlags.test( MODE_REPEAT ) ) {
        LCDSendMessage( LCD_SET_REPEAT_ON, 6 );
    } else {
        LCDSendMessage( LCD_SET_REPEAT_OFF, 6 );

    }
}

anTetrisSA::~anTetrisSA() { }

int anTetrisSA::Draw() {
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

        }
    } // end main loop

    return ( ret );
}