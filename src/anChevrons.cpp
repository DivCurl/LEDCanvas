#include "./include/anChevrons.h"

using namespace std;

anChevrons::anChevrons( npDisplay* pDisplay, mode_t mode, int frames, opt_t opts, scale_t customScaling ) 
: npAnimation( pDisplay, mode, frames, opts, customScaling ) {
    // Sync current animation runtime mode settings to LCD display
    if ( modeFlags.test( MODE_REPEAT ) ) {
        LCDSendMessage( LCD_SET_REPEAT_ON, 6 );   
    } else {
        LCDSendMessage( LCD_SET_REPEAT_OFF, 6 );   
    }      
}

anChevrons::~anChevrons() { }

int anChevrons::Draw() {
    angle = rand() % 360 ;
    int currentVertex = 51;
    int bottomVertex = 0;
    StartDelayCounter( 25 );
    
    // Main animation loop
    while ( ( framesDrawn < frames ) || modeFlags.test( MODE_REPEAT ) ) {
        if ( globalMode.msgPending ) {
            PollGlobalModes();  // handle any new external I/O messages
        }       
        
        if ( modeFlags.test( MODE_OFF ) ) {
            Clr();
        }  
        
        if ( ret == MODE_PREV || ret == MODE_NEXT ) {
            return ( ret );
        }
        
        if ( !skip ) {           
            static int dropNew = 1;
            static int count = 0;
            
            if ( ctrDelay.Done() ) {        
                
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
                } 
                
                else {    // gets the job done but need to clean this up...
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
                        }                         
                        else {    
                            break;
                        }
                    }
                }       
                
                ctrDelay.Reset(); 
                framesDrawn++;
            }   
            
            RefreshDisplay( FB_BLEND );
        } 
    } // end main loop
            
    return ( MODE_NEXT );
}