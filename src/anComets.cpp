#include "./include/anComets.h"

using namespace std;

anComets::anComets( npDisplay* pDisplay, mode_t mode, int frames, opt_t opts ) 
: npAnimation( pDisplay, mode, frames, opts ) {
    // Sync current animation runtime mode settings to LCD display
    if ( modeFlags.test( MODE_REPEAT ) ) {
        LCDSendMessage( LCD_SET_REPEAT_ON, 6 );   
    } else {
        LCDSendMessage( LCD_SET_REPEAT_OFF, 6 );   
    }
}

anComets::~anComets() { }

int anComets::Draw() {
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
                int rnd = rand() % 10;
                rnd += 10;
                comets.resize( rnd );    // randomize number of comets
                firstScan = 0;
                // controls fadeout rate (and thus trail length) for all saucers 
                StartDelayCounter( 75 );  
                ctrDelay.Reset();       
                // randomize starting positions, directions, and color
                for ( vector<comet>::iterator it = comets.begin(); it < comets.end(); it++ ) {
                    (*it).x = rand() % ( GetColRight() + 1 );
                    (*it).y = rand() % ( GetRowTop() + 1 );
                    (*it).color = rgbwGetByAngle( rand() % 360, rand() % 32 );  // throw a little white in there for good measure...
                    (*it).dir = rand() % DIR_MAX;       // randomize path direction
                    
                    if ( ( rnd = ( rand() % 350 ) ) < 150 ) {
                        rnd = 150;                
                    }
                    
                    (*it).speed.Start( rnd );
                    Set( (*it).x, (*it).y, (*it).color );
                }
            }

            if ( ctrDelay.Update() ) {        
                FadeOut();
                ctrDelay.Reset();
            }   
    
            for ( vector<comet>::iterator it = comets.begin(); it < comets.end(); it++ ) { // draw initial positions
                if ( (*it).speed.Update() ) {            
                    // check direction and wrap around to other side of display if we're at the edge
                    switch ( (*it).dir ) {         
                        case DIR_LEFT:
                            if ( (*it).x == GetColLeft() ) {
                                (*it).x = GetColRight();
                            } else {
                                (*it).x--;
                            }
                            
                            break;

                        case DIR_RIGHT:
                            if ( (*it).x == GetColRight() ) {
                                (*it).x = GetColLeft();
                            } else {
                                (*it).x++;
                            }
                            
                            break;

                        case DIR_UP:
                            if ( (*it).y == GetRowTop() ) {
                                (*it).y = GetRowBottom();
                            } else {
                                (*it).y++;
                            }
                            
                            break;

                        case DIR_DOWN:
                            if ( (*it).y == GetRowBottom() ) {
                                (*it).y = GetRowTop();
                            } else {
                                (*it).y--;
                            }
                            
                            break;

                        default:
                            break;
                    }
            
                    // Draw new position
                    Set( (*it).x, (*it).y, (*it).color );            
                    (*it).speed.Reset();            
                    framesDrawn++;
                }
            }            
        }
        
        RefreshDisplay();
    } // end main loop         
    
    return ( ret );
}
