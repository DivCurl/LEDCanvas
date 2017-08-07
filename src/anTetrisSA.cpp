#include "./include/anTetrisSA.h"

extern bool analyzerRun;
extern volatile bool FFTBufferReady;
extern short singleSidedFFT[ N ];

const coord2d_t tetrisBlocks[ 7 ][ 4 ] = {
    {   // O
        { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } 
    },
    {   // L
        { 0, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 }        
    },
    {   // L (mirrored)
        { 2, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 }
    },
    {   // Z
        { 1, 0 }, { 2, 0 }, { 0, 1 }, { 1, 1 }       
    },
    {   // S
        { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 }
    },
    {   // I
        { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 }
    },
    {   // T
        { 1, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 }
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
    int currBlock;
    int binCount = GetColCount() / 2;
    int defShiftTick = 200;
    int defRotTick = 300;
    int defFallTick = 200;
    int fastFallTick = 50;
    float movAvg = 0.0f;
    // Store collision coords in bins.
    // Each bin can have multiple collision coords hence the 2D vector
    // Note: x-axis bins are outer vector (rows) with corresponding lengths on inner vector (columns)
    vector< vector<coord2d_t> > collisionBinCols( 10, vector<coord2d_t>( 1, { 0, 0 } ) );
    counter shiftTick ( defShiftTick, ON );
    counter rotTick ( defRotTick, ON );
    counter fallTick ( defFallTick, ON );
    
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

    // Main loop
    while ( ( framesDrawn < frames ) || modeFlags.test( MODE_REPEAT ) ) {
        if ( globalMode.msgPending ) {
            PollGlobalModes();  // handle any new external I/O messages
        }

        if ( modeFlags.test( MODE_OFF ) ) {
            Clr();
        }

        if ( ret == MODE_PREV || ret == MODE_NEXT ) {
            return ( ret );  // break while loop and return to main signaling next/prev animation to be drawn
        }

        if ( !skip ) {
            if ( !gameOver ) {                
                
                if ( FFTBufferReady ) {
                    ComputeFFT();
                }
                                
                // We can rotate the piece on this step or move it left/right, but it has to fall
                // one row on the fall tick
                if ( shiftTick.Done() ) { // inPlay check ensures at least one block has been spawned on the screen      
                    shiftTick.Reset();           
                    
                    if ( blockMoving ) { 
                        bool collide = 0;                                        
                        float avg = 0.0f;
                                                
                        for ( int bin = 0; bin < binCount; bin++ ) {                    
                            avg += Remap ( singleSidedFFT[ bin ], -54, -20, 0, 10 );                    
                        }

                        avg /= binCount;
                        
                        if ( avg > 2.0f ) {                        
                            int rndShift = ( rand() % 3 ) - 1;  // randomizer for left/right shift by one
                            vector<sprite>::iterator itSprite = blocks.end() - 1;                                                

                            // Check for horizontal collision with another sprite or the screen extents
                            for ( vector<pixel>::iterator itPx = itSprite->GetPixelVec().begin(); itPx != itSprite->GetPixelVec().end(); ++itPx ) {    
                                coord2d_t testShift = { itPx->coord.x + rndShift, itPx->coord.y };
                                if ( ( sprite::CollideCheck( collisionBinCols, testShift ) & COLLIDE_LEFT ) || ( sprite::CollideCheck( collisionBinCols, testShift ) & COLLIDE_RIGHT ) ) {
                                    collide = 1;
                                    break;
                                }                        
                            }

                            if ( !collide ) {
                                itSprite->Shift( rndShift, 0 ); 

                                for ( vector<sprite>::iterator it = blocks.begin(); it != blocks.end(); ++it ) {
                                    Blit( it->GetPixelVec() );
                                }

                                RefreshDisplay( FB_CLEAR );
                                ++framesDrawn;   
                            }
                        }
                    }                  
                } // shift tick
                
                if ( rotTick.Done() ) {                      
                    rotTick.Reset();
                    
                    if ( blockMoving ) { 
                        bool collide = 0;      
                        float avg = 0.0f;                  
                        vector<sprite>::iterator itSprite = blocks.end() - 1;    
                        // Take average volume of all frequencies counted
                        for ( int bin = 0; bin < binCount; bin++ ) {                    
                            avg += Remap ( singleSidedFFT[ bin ], -54, -20, 0, 10 );                    
                        }

                        avg /= binCount;
                        // if ( rand() % 2 ) { 
                        if ( avg >= 4.5f ) {
                            sprite rotateBlock;
                            Matrix4 transform;
                            transform.RotateZ( 90.0f );
                            int xOffset = itSprite->GetLeftExtent();
                            int yOffset = itSprite->GetTopExtent();

                            // Get pixels from existing block and regen new sprite by rotation transform
                            for ( vector<pixel>::iterator itPx = itSprite->GetPixelVec().begin(); itPx != itSprite->GetPixelVec().end(); ++itPx ) {    
                                int x, y;; 
                                // Generate the new sprite
                                x = round( transform.m[ 0 ] * ( (float)itPx->coord.x - xOffset ) ) + round( transform.m[ 4 ] * ( (float)itPx->coord.y - yOffset ) );
                                y = round( transform.m[ 1 ] * ( (float)itPx->coord.x - xOffset ) ) + round( transform.m[ 5 ] * ( (float)itPx->coord.y - yOffset ) );
                                rotateBlock.AddPixels( pixel( { x + xOffset, y + yOffset }, itPx->GetColor() ) );
                            }

                            // Check for collision 
                            for ( vector<pixel>::iterator itPx = rotateBlock.GetPixelVec().begin(); itPx != rotateBlock.GetPixelVec().end(); ++itPx ) {    
                                if ( ( sprite::CollideCheck( collisionBinCols, itPx->coord ) & COLLIDE_LEFT_RIGHT ) ) {
                                    collide = 1;
                                    break;
                                }                        
                            }   
                            // Replace old sprite if no collision after rotation
                            if ( !collide ) {
                                (*itSprite) = rotateBlock;                        

                                for ( vector<sprite>::iterator it = blocks.begin(); it != blocks.end(); ++it ) {
                                    Blit( it->GetPixelVec() );
                                }

                                RefreshDisplay( FB_CLEAR );
                                ++framesDrawn;   
                            } 
                        }
                    }
                } // rotation tick

                // TODO: add checks to when lines complete
                if ( fallTick.Done() ) {
                    float avg = 0.0f;
                    fallTick.Reset();
                    
                    for ( int bin = 0; bin < binCount; bin++ ) {                    
                        avg += Remap ( singleSidedFFT[ bin ], -54, -20, 0, 10 );                    
                    }
                    
                    avg /= binCount;                    
                    // Update moving average
                    movAvg -= movAvg / 5;
                    movAvg += avg / 5;
                    // Increase/decrease fall speed as appropriate
                    if ( movAvg > 3.5f ) {
                        fallTick.SetDelay( fastFallTick );
                    } 
                    else {
                        fallTick.SetDelay ( defFallTick );
                    }
                    
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
                                // If we're colliding immediately after spawn, no more moves...
                                if ( !vertShifts ) {
                                    ret = MODE_NEXT;
                                }                            
                                
                                break;                                                                   
                            }                                                         
                        }
                        
                        if ( blockMoving ) {                        
                            itSprite->Shift( 0, -1 );
                            ++vertShifts;
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

    return ( MODE_NEXT );
}

// Spawn random Tetris block
// Grab a random block number
// then add corresponding pixels to the current sprite vector.
// The current block sprite being handled by the animation
// loop will always be the last element of the sprite vector
bool anTetrisSA::SpawnBlock( float dispCenter, int block ) {
    uint16_t  xMin, xMax, spriteCenter;
    sprite newBlock;   
    vertShifts = 0;
    
    for ( int i = 0; i < 4; i++ ) { // 4 total pixels per block
        // New pieces always spawn with horizontal orientation, pointing down (first element in block's rotation table)
        newBlock.AddPixels( pixel( tetrisBlocks[ block ][ i ], blockColors[ block ] ) );
        // Get x-axis length of sprite
        if ( tetrisBlocks[ block ][ i ].x < xMin ) {
            xMin = tetrisBlocks[ block ][ i ].x;
        }         
        else if ( tetrisBlocks[ block ][ i ].x > xMax ) {
            xMax = tetrisBlocks[ block ][ i ].x;
        }
    }
    
    spriteCenter = ( xMax - xMin ) / 2.0f; 
    // TODO: Still need to tweak this...blocks aren't always centered 
    newBlock.Translate( { (int)dispCenter - spriteCenter, 30 } ); // move to top-center of display (it's OK if we overflow the screen boundary)
    blocks.push_back( newBlock );

    return ( 0 );
}