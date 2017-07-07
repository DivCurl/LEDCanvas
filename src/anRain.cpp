#include "./include/anRain.h"

using namespace std;

anRain::anRain( npDisplay* pDisplay, mode_t mode, int frames, opt_t opts ) 
: npAnimation( pDisplay, mode, frames, opts ) { }

anRain::~anRain() { }

int anRain::Draw() {
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
                StartDelayCounter( 50 );         
                ctrDelay.Reset(); 
            }
    
            if ( ctrDelay.Update() ) {
                int i, r_i, rnd;
                rnd = rand() % ( 4 );           // max random number of 'droplets' to start with on top row every cycle
                ShiftDown();
                
                for ( i = 0; i <= rnd; i++ ) {
                    r_i = rand() % ( pDisplay->GetNumNeopixels() );  // determine where to put the pixels
                    // dummy = rand() % 360;    // random color
                    Set( r_i, GetRowTop(), rgbwGetByAngle( angle, 0 ) );    // rainbow colored drops
                }

                if ( ( angle += 1.0f )  > 360 ) { 
                    angle -= 360;
                }

                ctrDelay.Reset(); 
                framesDrawn++;
            }            
        }
        
        RefreshDisplay();
    } // end while loop         
    
    return ( ret );
}

int anRain::Init() {
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