#include "./include/anTetrisSA.h"

extern bool analyzerRun;
extern volatile bool FFTBufferReady;
extern short singleSidedFFT[ N ];

const coord2d_t tetrisBlocks[ 7 ][ 4 ][ 4 ] = {
    {   // O
        { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } }, // all rotations identical for this block
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

anTetrisSA::anTetrisSA( npDisplay* pDisplay, mode_t mode, int frames, opt_t opts, scale_t customScaling )
: npAnimation( pDisplay, mode, frames, opts, customScaling ) {
    float startColor = 0; //rand() % 360;
    float clrMult = 360 / MAX_PIECES;
    
    // Sync current animation runtime mode settings to LCD display
    if ( modeFlags.test( MODE_REPEAT ) ) {
        LCDSendMessage( LCD_SET_REPEAT_ON, 6 );
    } else {
        LCDSendMessage( LCD_SET_REPEAT_OFF, 6 );

    }
    // Assign colors to blocks 
    for ( int i = 0; i < MAX_PIECES; i++ ) {
        blockColors[ i ] = rgbwGetByAngle( startColor + ( i * clrMult ) );
    }
    
    analyzerRun = 1;    // used by T4 ISR
    InitFFT();
}

anTetrisSA::~anTetrisSA() { 
    analyzerRun = 0;
}

int anTetrisSA::Draw() {
        // Store collision coords in bins.
    // Each bin can have multiple collision coords hence the 2D vector
    // Note: x-axis bins are outer vector (rows) with corresponding lengths on inner vector (columns)
    vector< vector<coord2d_t> > collisionBinCols( 10, vector<coord2d_t>( 1, { 0, 0 } ) );
    counter mainTick ( 150, ON );
    counter fallTick ( 75, ON );
    int currBlock;

    // initialize the collision envelope to 1 less the bottom row of the display
    for ( vector< vector<coord2d_t> >::iterator itBin = collisionBinCols.begin(); itBin != collisionBinCols.end(); ++itBin ) {
        itBin->reserve( 64 );   // reserve enough RAM for the inner vectors         
        // Generate initial collision envelope coords -1 row below the bottom display row
        for ( vector<coord2d_t>::iterator itVal = itBin->begin(); itVal != itBin->end(); ++itVal ) {
            int i = itBin - collisionBinCols.begin();   // for indexing
            itVal->x = i;
            itVal->y = -1;
        }
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
                if ( FFTBufferReady ) {
                    ComputeFFT();
                }
                // We can rotate the piece on this step or move it left/right, but it has to fall
                // one row on the fall tick
                if ( mainTick.Done() ) { // inPlay check ensures at least one block has been spawned on the screen      
                    mainTick.Reset();           
                    
                    if ( blockMoving ) { 
                        int rndShift = ( rand() % 3 ) - 1;
                        vector<sprite>::iterator itSprite = blocks.end() - 1;

                        bool colliding = 0;                                        
                        for ( vector<pixel>::iterator itPx = itSprite->GetPixelVec().begin(); itPx != itSprite->GetPixelVec().end(); ++itPx ) {    
                            coord2d_t testShift = { itPx->coord.x + rndShift, itPx->coord.y };
                            if ( ( sprite::CollideCheck( collisionBinCols, testShift ) & COLLIDE_LEFT ) || ( sprite::CollideCheck( collisionBinCols, testShift ) & COLLIDE_RIGHT ) ) {
                                colliding = 1;
                                break;
                            }                        
                        }

                        // Test rotation and check for collisions. 
                        for ( int i = 0; i < 4; i++ ) { 
                            // TODO
                        }
                        
                        // OK
                        if ( !colliding ) {
                            itSprite->Shift( rndShift, 0 ); 

                            for ( vector<sprite>::iterator it = blocks.begin(); it != blocks.end(); ++it ) {
                                Blit( it->GetPixelVec() );
                            }

                            RefreshDisplay( FB_CLEAR );
                            ++framesDrawn;   
                        }                
                    }                                        
                } // main tick

                // TODO: add checks for lines 
                if ( fallTick.Done() ) {
                    fallTick.Reset();
                    
                    if ( !blockMoving ) {
                        currBlock = rand() % MAX_PIECES;
                        SpawnBlock( GetDisplayCenter(), currBlock );              
                        blockMoving = 1;
                    }                     
                    else {
                        vector<sprite>::iterator itSprite = blocks.end() - 1;
                        // Loop through sprite's pixels and check collision against collision envelope vector
                        for ( vector<pixel>::iterator itPx = itSprite->GetPixelVec().begin(); itPx != itSprite->GetPixelVec().end(); ++itPx ) {         
                            // Test for collision against any lower sprite coordinates
                            if ( sprite::CollideCheck( collisionBinCols, { itPx->coord.x, itPx->coord.y - 1 } ) & COLLIDE_BOTTOM ) { // oollision detected                                
                                blockMoving = 0;
                                /*
                                 * TODO: Add End Game checks here
                                 */                               
                                break;                                                                   
                            }                                                         
                        }
                        
                        if ( blockMoving ) {                        
                            itSprite->Shift( 0, -1 );                             
                        }
                        else { 
                            sprite::AddCollisionEnvCoords( collisionBinCols, itSprite->GetPixelVec() );
                        }
                    }

                    // Blit all sprites to the screen
                    for ( vector<sprite>::iterator it = blocks.begin(); it != blocks.end(); ++it ) {
                        Blit( it->GetPixelVec() );
                    }

                    RefreshDisplay( FB_CLEAR );
                    ++framesDrawn;
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
bool anTetrisSA::SpawnBlock( float dispCenter, int block ) {
    uint16_t  xMin, xMax, spriteCenter;
    sprite newBlock;
    
    for ( int i = 0; i < 4; i++ ) { // 4 total pixels per block
        // New pieces always spawn with horizontal orientation, pointing down (first element in block's rotation table)
        newBlock.AddPixels( pixel( tetrisBlocks[ block ][ 0 ][ i ], blockColors[ block ] ) );
        // Get x-axis length of sprite
        if ( tetrisBlocks[ block ][ 0 ][ i ].x < xMin ) {
            xMin = tetrisBlocks[ block ][ 0 ][ i ].x;
        }         
        else if ( tetrisBlocks[ block ][ 0 ][ i ].x > xMax ) {
            xMax = tetrisBlocks[ block ][ 0 ][ i ].x;
        }
    }

    spriteCenter = ( xMax - xMin ) / 2.0f; 
    // Still need to tweak this...blocks aren't always centered 
    newBlock.Translate( { (int)dispCenter - spriteCenter, 59 } ); // move to top-center of display (it's OK if we overflow the screen boundary)
    //newBlock.Translate( { 3, 59 } ); 
    blocks.push_back( newBlock );

    return ( 0 );
}