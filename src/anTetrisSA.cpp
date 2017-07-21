#include "./include/anTetrisSA.h"

using namespace std;

// 
const coord2d_t tetrisBlocks[ 5 ][ 4 ][ 4 ] = {
    {   // O
        { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } }, // all rotations identical (this block only)
        { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } },       
        { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } },
        { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } } 
    }, 
    {   // L
        { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 0 } }, // rotation 0
        { { 0, 0 }, { 0, 1 }, { 1, 1 }, { 1, 2 } }, // rotation 1
        { { 0, 0 }, { 1, 0 }, { 2, 0 }, { 2, 1 } }, // rotation 2
        { { 0, 1 }, { 1, 1 }, { 2, 1 }, { 2, 0 } }  // rotation 3
    }, 
    {   // Z
        { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 } }, // etc ...
        { { 0, 1 }, { 1, 1 }, { 1, 0 }, { 2, 0 } },
        { { 0, 1 }, { 0, 2 }, { 1, 1 }, { 1, 0 } },
        { { 0, 0 }, { 0, 1 }, { 1, 1 }, { 1, 2 } },
    }, 
    {   // I
        { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 } },
        { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 } },
        { { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 } },
        { { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 } },    
    }, 
    {   // T
        { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 0 } },
        { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 0 } },
        { { 0, 1 }, { 1, 0 }, { 1, 1 }, { 1, 2 } },
        { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 1 } },
    }    
};

// 9 * 60 = 540 pixels * 1 shape / 4 pixels = 135 shapes
// pixel shapes[ 135 ] [ 4 ];

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
    // Create a vector of shapes
    
    counter ctrMain ( 1000, ON );
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
            // while ( !gameOver ) ... 
            
            if ( ctrMain.Update() ) {
                ctrMain.Reset();   
                // Start at step 0 - this will be the first shape
                // Get two random numbers; 1) the shape (which structure to pull from), and 2) the initial rotation of the shape
                // Testing - let's just get two shapes and put them on the display
                
                /*
                shapes[ 0 ][ 0 ].coord = tetris_T[ 0 ][ 0 ];
                shapes[ 0 ][ 1 ].coord = tetris_T[ 0 ][ 1 ];
                shapes[ 0 ][ 2 ].coord = tetris_T[ 0 ][ 2 ];
                shapes[ 0 ][ 3 ].coord = tetris_T[ 0 ][ 3 ];
                shapes[ 0 ][ 0 ].color = rgbwGetByAngle( 0 );
                shapes[ 0 ][ 1 ].color = rgbwGetByAngle( 0 );
                shapes[ 0 ][ 2 ].color = rgbwGetByAngle( 0 );
                shapes[ 0 ][ 3 ].color = rgbwGetByAngle( 0 );               
                
                Set( shapes[ 0 ][ 0 ] );
                Set( shapes[ 0 ][ 1 ] );
                Set( shapes[ 0 ][ 2 ] );
                Set( shapes[ 0 ][ 3 ] );                
                 */
                
                RefreshDisplay( FB_CLEAR );
                framesDrawn++;
             }
        }
    } // end main loop

    return ( ret );
}

// Spawn random tetris piece
// Grab a random piece number and rotation, 
// then add corresponding pixels to sprite vector
// The current sprite being handled by the animation
// loop will always be at the tail end of the sprite vector
bool anTetrisSA::SpawnBlock() {
    uint8_t rndBlock = rand() % MAX_PIECES;
    uint8_t rndRot = rand() % MAX_ROTATIONS;
    uint8_t rndColor = rand() % 360;
    sprite newBlock;
    
    for ( int i = 0; i < 4; i++ ) {
        newBlock.AddPixels( pixel( tetrisBlocks[ rndBlock ][ rndRot ][ i ], rgbwGetByAngle( rndColor ) ) );
    }
    
    newBlock.Translate( { 4, 59 } );    // move to top-center of display (it's OK if we overflow the screen boundary)
    newBlock.SetMoving();
    blocks.push_back( newBlock );
    
    return ( 0 );
}