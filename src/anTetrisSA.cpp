#include "./include/anTetrisSA.h"

using namespace std;

const coord2d_t tetrisBlocks[ 7 ][ 4 ][ 4 ] = {
    {   // O
        { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } }, // all rotations identical (this block only)
        { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } },
        { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } },
        { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } }
    },
    {   // L
        { { 0, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } }, // rotation 0
        { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 0, 2 } }, // rotation 1
        { { 0, 0 }, { 1, 0 }, { 2, 0 }, { 2, 1 } }, // rotation 2
        { { 1, 0 }, { 1, 1 }, { 1, 2 }, { 0, 2 } }  // rotation 3
    },
    {   // L (mirrored)
        { { 2, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } },
        { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 2 } },
        { { 0, 0 }, { 1, 0 }, { 2, 0 }, { 0, 1 } },
        { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 1, 2 } }
    },
    {   // Z
        { { 1, 0 }, { 2, 0 }, { 0, 1 }, { 1, 1 } },
        { { 0, 0 }, { 0, 1 }, { 1, 1 }, { 1, 2 } },
        { { 1, 0 }, { 2, 0 }, { 0, 1 }, { 1, 1 } },
        { { 0, 0 }, { 0, 1 }, { 1, 1 }, { 1, 2 } }
    },
    {   // S
        { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 } },
        { { 1, 0 }, { 0, 1 }, { 1, 1 }, { 0, 2 } },
        { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 } },
        { { 1, 0 }, { 0, 1 }, { 1, 1 }, { 0, 2 } }
    },
    {   // I
        { { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 } },
        { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 } },
        { { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 } },
        { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 } },
    },
    {   // T
        { { 1, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } },
        { { 0, 0 }, { 0, 1 }, { 1, 1 }, { 0, 2 } },
        { { 0, 0 }, { 1, 0 }, { 2, 0 }, { 1, 1 } },
        { { 1, 0 }, { 0, 1 }, { 1, 1 }, { 1, 2 } }
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

    // Randomize block colors
    float startColor = 0; //rand() % 360;
    float clrMult = 360 / MAX_PIECES;
    for ( int i = 0; i < MAX_PIECES; i++ ) {
        blockColors[ i ] = rgbwGetByAngle( startColor + ( i * clrMult ) );
    }
}

anTetrisSA::~anTetrisSA() { }

int anTetrisSA::Draw() {
    vector<sprite>::iterator itSprites;
    // Store collision coords in bins.
    // Each bin can have multiple collision coords hence the vector
    // Note: x-axis bins are outer vector (rows) with corresponding lengths on inner vector (columns)
    vector< vector<coord2d_t> > collisionBinCols( GetColCount(), vector<coord2d_t>( 1, { 0, 0 } ) );
    sprite fallingBlock;
    counter mainTick ( 50, ON );
    counter fallTick ( 100, ON );
    int i = 0;
    // initialize the collision envelope to 1 less the bottom row of the display
    for ( vector< vector<coord2d_t> >::iterator itBins = collisionBinCols.begin(); itBins != collisionBinCols.end(); ++itBins ) {
        for ( vector<coord2d_t>::iterator itVals = itBins->begin(); itVals != itBins->end(); ++itVals ) {
            // int i = itBins - collisionBinCols.begin();   // for indexing
            itVals->x = i;
            itVals->y = -1;
        }
        
        ++i;
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
            if ( !gameOver ) {
                // We can rotate the piece on this step or move it left/right, but it has to fall
                // one row on the next tick
                if ( mainTick.Done() ) {
                    mainTick.Reset();
                    //
                    // ROTATIONS AND SHIFTS DUE TO MUSIC HERE
                    //
                }

                if ( fallTick.Done() ) {
                    fallTick.Reset();

                    if ( !blockMoving ) {
                        SpawnBlock();
                        // Point iterator to new block
                        itSprites = blocks.end() - 1;
                        // Assign to working sprite variable
                        // I'm having to do this because for some reason (*itSprites).Shift( 0, -1 ) doesn't work??
                        // Will investigate further but low priority for now
                        fallingBlock = (*itSprites);    
                        blockMoving = 1;
                    } else {
                        fallingBlock.Shift( 0, -1 ); // move block sprite to next row
                        /* VERISON 1 - SPRITE-LEVEL COLLISION */
                        /* WORKS PARTIALLY BUT DOESN'T CAPTURE COLLISIONS AT THE PIXEL-LEVEL RESOLUTION */
                        // Check collision envelope and update enevelope coords if collision found
                        /*
                        if ( int colPos = fallingBlock.CollideCheck( colEnvelope ) ) {
                            // outer loop: envelope coords
                            for ( vector<coord2d_t>::iterator itEnv = colEnvelope.begin(); itEnv != colEnvelope.end(); itEnv++ ) {
                                // inner loop: the falling sprite's pixel vector
                                for ( vector<pixel>::iterator itPx = fallingBlock.GetPixelVec().begin(); itPx != fallingBlock.GetPixelVec().end(); itPx++ ) {
                                    if ( colPos &= COLLIDE_BOTTOM ) {
                                        blockMoving = 0;
                                        if ( (*itPx).coord.y >= (*itEnv).y ) {
                                            (*itEnv).y = (*itPx).coord.y;
                                        }
                                    }
                                }
                            }
                        }
                        */

                        // VERSION 2 - PER PIXEL COLLISION -- TESTING / IN PROGRESS
                        // Loop through sprite's pixels and check collision against collision envelope vector
                        for ( vector<pixel>::iterator itPx = fallingBlock.GetPixelVec().begin(); itPx != fallingBlock.GetPixelVec().end(); ++itPx ) {                            
                            if ( int colPos = sprite::CollideCheck( collisionBinCols, (*itPx) ) ) { // oollision detected
                                // Check specific collisions and update envelope for the respective x-axis
                                // for ( vector<coord2d_t>::iterator itBinVals = collisionBinCols[ colPos ].begin(); itBinVals != collisionBinCols[ colPos ].end(); ++itBinVals ) {
                                // vector<coord2d_t>::iterator itBinVal = collisionBinCols[ colPos ].end() - 1; // last coord in x-axis vector is always the 'largest'

                                if ( colPos &= COLLIDE_BOTTOM ) {   // Redundant if statement? Can this check be done inline with previous if?
                                    blockMoving = 0;
                                    // Check the largest y-coord on this bin.
                                    // If this pixels's y-coord is greater, add this pixels coords to the envelope vector
                                    /* THIS DOESN'T WORK 
                                    if ( itPx->coord.y > itBinVal->y ) {
                                        (*itBinVal) = itPx->coord;
                                     }
                                    */
                                    
                                    
                                    //
                                    // Test for no more moves (set gameOver bit) here
                                    // 

                                    // Add this sprite's pixels to the existing envelope vector                                                                        
                                    sprite::AddCollisionEnvCoords( collisionBinCols, fallingBlock.GetPixelVec() );
                                    break;                                   
                                }
                            }
                        }                                                
                    }

                    blocks.at( blocks.size() - 1 ) = fallingBlock; // assign working sprite back to sprite vector
                    // Blit all sprites to the screen
                    for ( itSprites = blocks.begin(); itSprites != blocks.end(); itSprites++ ) {
                        Blit( (*itSprites).GetPixelVec() );
                    }

                    RefreshDisplay( FB_CLEAR );
                    framesDrawn++;
                } // fall tick
            }
        }
    } // end main loop

    return ( ret );
}

// Spawn random Tetris block
// Grab a random block number
// then add corresponding pixels to the current sprite vector.
// The current block sprite being handled by the animation
// loop will always be the last element of the sprite vector
bool anTetrisSA::SpawnBlock() {
    uint8_t rndBlock = rand() % MAX_PIECES;
    sprite newBlock;

    for ( int i = 0; i < 4; i++ ) {
        // New pieces always spawn with horizontal orientation, pointing down (first element in block's rotation table)
        newBlock.AddPixels( pixel( tetrisBlocks[ rndBlock ][ 0 ][ i ], blockColors[ rndBlock ] ) );
    }

    newBlock.Translate( { 3, 59 } );    // move to top-center of display (it's OK if we overflow the screen boundary)
    blocks.push_back( newBlock );

    return ( 0 );
}