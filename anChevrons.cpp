#include <stdio.h>
#include "anChevrons.h"

using namespace std;

anChevrons::anChevrons( npDisplay* pDisplay, int frames, int id, mode_t mode ) 
: npAnimation( pDisplay, frames, id, mode ) {
    
}

anChevrons::~anChevrons() {    
    
}

int anChevrons::Draw() {
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
            static int bottomVertex; // this tracks the lowest-most chevron vertex currently drawn
            static int currentVertex;
            static int dropNew = 1;
            static int shiftOut = 0;
            static int count = 0;
            if ( firstScan ) { 
                Clr();
                firstScan = 0;
                angle = rand() % 360 ;
                currentVertex = 51;
                bottomVertex = 0;
                StartDelayCounter( 50 );         
                ctrDelay.Reset();       
            }
    
            if ( ctrDelay.Update() ) {        
                if ( dropNew ) {            
                    currentVertex = 51;
                    if ( count == 3 ) {
                        if ( ( angle += 5.0 ) > 360 ) {
                            angle -= 360;
                        }
                        count = 0;
                    }            
                    Set( 0, currentVertex + 8, rgbwGetByAngle( angle  ) );
                    Set( 1, currentVertex + 6, rgbwGetByAngle( angle ) );
                    Set( 2, currentVertex + 4, rgbwGetByAngle( angle ) );
                    Set( 3, currentVertex + 2, rgbwGetByAngle( angle ) );
                    Set( 4, currentVertex, rgbwGetByAngle( angle ) );
                    Set( 5, currentVertex + 2, rgbwGetByAngle( angle ) );
                    Set( 6, currentVertex + 4, rgbwGetByAngle( angle ) );
                    Set( 7, currentVertex + 6, rgbwGetByAngle( angle ) );
                    Set( 8, currentVertex + 8, rgbwGetByAngle( angle ) );         
                    count++;            
                    dropNew = 0;

                } else {    // gets the job done but need to clean this up...
                    Clr( 0, currentVertex + 8 );
                    Clr( 1, currentVertex + 6 );
                    Clr( 2, currentVertex + 4 );
                    Clr( 3, currentVertex + 2 );
                    Clr( 4, currentVertex );
                    Clr( 5, currentVertex + 2 );
                    Clr( 6, currentVertex + 4 );
                    Clr( 7, currentVertex + 6 );
                    Clr( 8, currentVertex + 8 );

                    Set( 0, currentVertex + 7, rgbwGetByAngle( angle  ) );
                    Set( 1, currentVertex + 5, rgbwGetByAngle( angle ) );
                    Set( 2, currentVertex + 3, rgbwGetByAngle( angle ) );
                    Set( 3, currentVertex + 1, rgbwGetByAngle( angle ) );
                    Set( 4, currentVertex - 1, rgbwGetByAngle( angle ) );
                    Set( 5, currentVertex + 1, rgbwGetByAngle( angle ) );
                    Set( 6, currentVertex + 3, rgbwGetByAngle( angle ) );
                    Set( 7, currentVertex + 5, rgbwGetByAngle( angle ) );
                    Set( 8, currentVertex + 7, rgbwGetByAngle( angle ) );  

                    currentVertex--;                                    
                    if ( currentVertex == bottomVertex ) {
                        if ( bottomVertex++ != 50 ) {
                            dropNew = 1;
                        } else {    // Done - restart
                            firstScan = 1;
                            return ( FRAME_DRAWN );
                        }
                    }
                }       
                
                ctrDelay.Reset(); 
                framesDrawn++;
            }   
            RefreshDisplay();
        } 
    }// end while loop         
    
    return ( ret );
}

int anChevrons::Init() {
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