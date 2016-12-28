#include <stdio.h>
#include "anPatterns.h"

using namespace std;

anPatterns::anPatterns( npDisplay* pDisplay, int frames, int id, mode_t mode ) 
: npAnimation( pDisplay, frames, id, mode ) {
    
}

anPatterns::~anPatterns() {    
    
}

int anPatterns::Draw() {
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
                case ID_PATTERN_RAINBOW_1:
                    if ( RainbowChaser1() ) {
                        framesDrawn++;
                    }
                    break;

                case ID_PATTERN_RAIN:
                    if ( Rain() ) {
                        framesDrawn++;
                    }
                    break;

                case ID_PATTERN_FADE_MIDDLE:
                    if ( FadeToMiddle() ) {
                        framesDrawn++;
                    }                    
                    break;

                case ID_PATTERN_RANDOM_FILL:
                    if ( RandomFill() ) {
                        framesDrawn++;
                    }                    
                    break;    

                case ID_PATTERN_CHEVRONS:
                    if ( StackedChevrons() ) {
                        framesDrawn++;
                    }                    
                    break;  
                    
                case ID_PATTERN_COMETS:
                    if ( Comets() ) {
                        framesDrawn++;
                    }                    
                    break;  
                    
                case ID_PATTERN_FIREWORKS:
                    if ( FireWorks() ) {
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

int anPatterns::Init() {
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
 
bool anPatterns::RainbowChaser1() {
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
        return ( FRAME_DRAWN );
       
    }
    return ( FRAME_SKIP );
}

bool anPatterns::FadeToMiddle() {
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
        return ( FRAME_DRAWN );
       
    }
     
    return ( FRAME_SKIP );  
}

bool anPatterns::Rain() {
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
        return ( FRAME_DRAWN );
    }
    
    return ( FRAME_SKIP );
}

bool anPatterns::RandomFill() {     
    if ( firstScan ) {        
        firstScan = 0;
        angle = 0;
        StartDelayCounter( 100 );  
        ctrDelay.Reset(); 
    }
    
    if ( ctrDelay.Update() ) {
        // FadeOut();
        int rnd1, rnd2;
        for ( int i = 0; i <= GetColRight(); i++ ) {
            rnd1 = rand() % 2;
            for ( int j = 0; j <= rnd1; j++ ) {
                rnd2 = rand() % ( 59 + 1 );
                Set( i, rnd2, rgbwGetByAngle( rand() % 360, 0 ) );  
            }
        }
        
        if ( ( angle += 2.0f )  > 360 ) { 
            angle -= 360;
        }
        
        ctrDelay.Reset(); 
        return ( FRAME_DRAWN );
    }
    
    return ( FRAME_SKIP );
}

bool anPatterns::StackedChevrons() {
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
        return ( FRAME_DRAWN );
    }
    
    return ( FRAME_SKIP );
}

bool anPatterns::Comets() {
    int ret = FRAME_SKIP;
    if ( firstScan ) {        
        int rnd;
        rnd = rand() % 10;
        rnd += 10;
        
        saucers.resize( rnd );    // number of saucers
        firstScan = 0;
        // controls fadeout rate (and thus trail length) for all saucers 
        // NOTE: might need to have individual counter for each saucer...will see after testing
        StartDelayCounter( 75 );  
        ctrDelay.Reset();       
        // randomize starting positions, directions, and color
        for ( vector<flySaucer>::iterator it = saucers.begin(); it < saucers.end(); it++ ) {
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
   
    
    for ( vector<flySaucer>::iterator it = saucers.begin(); it < saucers.end(); it++ ) { // draw initial positions
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
            ret = FRAME_DRAWN;
        }            
    }

    return ( ret );    
}

bool anPatterns::FireWorks() {
/* 
 * 1. Randomize starting position (not too far from center)
 * 2. Randomize 'explode' (y) position
 * 3. Determine number of explosion particles
 * 4. Launch the firework
 * 5. Explode - 2-3 steps? Concentrate particles around starting position
 * 6. Allow the particles to fall & fade out
  */    
    int launchSpeed = 0;
    if ( firstScan ) {
        firstScan = 0;
        step = 0;
        fireWorks.particles.resize( 10 );        
        StartDelayCounter( 100 );  
        ctrDelay.Reset();                   
    }
    
    if ( ctrDelay.Update() ) {
        FadeOut();
        ctrDelay.Reset();
    }
    
    switch ( step ) {
        // launch
        case 0:
            fireWorks.y = 0;
            fireWorks.x = rand() % 3;
            fireWorks.x += 2;
            fireWorks.yExplode = rand() % 40;
            fireWorks.yExplode += 20;
            launchSpeed = rand() % 50;
            launchSpeed += 25;
            fireWorks.launchSpeed.Start( launchSpeed ); 
            step = 1;
            break;
        case 1: 
            if ( fireWorks.launchSpeed.Update() ) {
                if ( fireWorks.y != fireWorks.yExplode ) {
                    fireWorks.y++;
                    Set( fireWorks.x, fireWorks.y, rgbwGetByAngle( 0, 255 ) );
                } else {
                    // get the starting position of the particles
                    for ( int i = 0; i < fireWorks.particles.size(); i++  ) {
                        fireWorks.particles[i].x = rand() % 4;
                        fireWorks.particles[i].x += 2;  // ensure we're not too close to the sides
                        fireWorks.particles[i].y = fireWorks.yExplode;  // all starting at same height
                        fireWorks.delta[i].x = 1-(float)(rand() % 200) / 100;   // 0-0.99
                        // Set( fireWorks.particles[i].x, fireWorks.particles[i].y, rgbwGetByAngle( 0 ) );
                    }                    
                    
                    fireWorks.dropSpeed.Start( 350 );   // start the 'falling' speed counter                    
                    fireWorks.launchSpeed.Stop();
                    // step = 5;
                    break;
                } 
                
                fireWorks.launchSpeed.Reset();
            }
            break;
            
        // generate explode frame 1
        case 5:
            if ( fireWorks.dropSpeed.Update() ) {
                // update positions and let 'debris' fall
                for ( int i = 0; i < fireWorks.particles.size(); i++  ) {
                        fireWorks.delta[i].x = 1-(float)(rand() % 200) / 100; // 0-0.99
                        fireWorks.particles[i].y--;
                        Set( fireWorks.particles[i].x, fireWorks.particles[i].y, rgbwGetByAngle( angle ) );
                        fireWorks.dropSpeed.SetDelay( fireWorks.dropSpeed.GetDelay() * 0.9 );
                        fireWorks.dropSpeed.Reset();
                }
            }
            
            break;

        // generate explode frame 2
        case 10:
            break;
            
       // generate explode frame 3
        case 15:
            break;
            
        // generate explode frame 4
        case 20:
            break;
            
        case 25:
            break;
            
        case 30:
            break;
            
        default:
            break;
    }  
    
    return ( FRAME_DRAWN );
}