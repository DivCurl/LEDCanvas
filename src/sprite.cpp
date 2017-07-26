#include "./include/sprite.h"

using namespace std;

sprite::sprite() { }

sprite::~sprite() { }

void sprite::AddPixels( const pixel& px ) {
    pixels.push_back( px );
}   

// Append a vector of pixels to the existing pixel vector
// Does not check for duplicates!
void sprite::AddPixels( const vector<pixel>& px ) {
    pixels.insert( std::end( pixels ), std::begin( px ), std::end( px ) );
}

// Set color of entire sprite
void sprite::SetColor( rgbw_t color ) {
    
    for ( vector<pixel>::iterator it = pixels.begin(); it != pixels.end(); it++ ) {
        (*it).color = color;
    }
}

// Clear the color of all pixels of the sprite
void sprite::ClrColor() {
    for ( vector<pixel>::iterator it = pixels.begin(); it != pixels.end(); it++ ) {
        (*it).color = { 0, 0, 0, 0 };
    }
}

void sprite::Translate( coord2d_t transCoord ) {
    // The first pixel is the anchor of the sprite.
    vector<pixel>::iterator it = pixels.begin();
    coord2d_t newOrigin;
    newOrigin.x = transCoord.x - (*it).coord.x;
    newOrigin.y = transCoord.y - (*it).coord.y;
    
    for ( it; it != pixels.end(); it++ ) {
        (*it).coord += newOrigin;
        
    }
}

void sprite::Shift( int x, int y ) {
    for ( vector<pixel>::iterator it = pixels.begin(); it != pixels.end(); it++ ) {
        (*it).coord.x += x;
        (*it).coord.y += y;
        
    }
}

// Check if collision exists against a vector of sprites
/*
bool sprite::CollideCheck( const vector<sprite>& inSprites, coord2d_t testPos ) {
    vector<sprite>::const_iterator itInSprite;
    vector<pixel>::const_iterator itInPixel;
    vector<pixel>::iterator itThisPixel;
    
    // brute force for now; will optimize later if I can find the time
    // compare pixel coords of this sprite object  (+/- the test position coords) to all of the sprites in the 
    // target sprite vector. If any coords match, we have a collision
    for ( itInSprite = inSprites.begin(); itInSprite != inSprites.end(); itInSprite++ ) {   // loop through all input sprites
        for ( itThisPixel = pixels.begin(); itThisPixel != pixels.end(); itThisPixel++ ) {  
            for ( itInPixel = (*itInSprite).pixels.begin(); itInPixel != (*itInSprite).pixels.end(); itInPixel++ ) {
                // calculate coordinates of new would-be location of pixel
                int newSrcX = ( testPos.x > (*itThisPixel).coord.x ) ? testPos.x + (*itThisPixel).coord.x : testPos.x  - (*itThisPixel).coord.x;
                int newSrcY = ( testPos.y > (*itThisPixel).coord.y ) ? testPos.y + (*itThisPixel).coord.y : testPos.y  - (*itThisPixel).coord.y;
                
                if ( ( newSrcX == (*itInPixel).coord.x ) || ( newSrcY == (*itInPixel).coord.y ) ) {
                    return ( 1 );
                }                
            }
        }
    } 
    
    return ( 0 );
}
*/

/*** TODO: NEED TO CHECK PER-PIXEL COLLISION ***/

// Check if collision exists with a single sprite
int sprite::CollideCheck( const vector<coord2d_t>& env ) {
    int collidePos = 0;
    // vector<pixel> px = spr
    vector<pixel>::const_iterator itPixels;
    
    for ( itPixels = pixels.begin(); itPixels != pixels.end(); itPixels++ ) {
        // Check if any pixel is against the left wall
        if ( ( (*itPixels).coord.x - 1 ) == 0 ) {   // FIX MAGIC NUMBER
            collidePos |= COLLIDE_LEFT;
        }
        
        // Check if any pixel is against the right wall
        if ( ( (*itPixels).coord.x + 1 ) == 59 ) {   // FIX MAGIC NUMBER
            collidePos |= COLLIDE_RIGHT;
        }
        
        /*** TODO: NEED TO CHECK PER-PIXEL COLLISION ***/
        // Check if any pixel is against the envelope row
        for ( vector<coord2d_t>::const_iterator itEnv = env.begin(); itEnv != env.end(); itEnv++ ) {
            if ( ( (*itPixels).coord.x + 1 ) == (*itEnv).x ) {
                collidePos |= COLLIDE_RIGHT;
            }
            
            if ( ( (*itPixels).coord.x - 1 ) == (*itEnv).x ) {
                collidePos |= COLLIDE_LEFT;
            }
            
            if ( ( (*itPixels).coord.y + 1 ) == (*itEnv).y ) {
                collidePos |= COLLIDE_TOP;
            }
            
            if ( ( (*itPixels).coord.y - 1 ) == (*itEnv).y ) {
                collidePos |= COLLIDE_BOTTOM;
            }
        }        
    }
    
    return ( collidePos );
}

// Per-pixel collision detection
int sprite::CollideCheck( const vector< vector<coord2d_t> >& env, const pixel& px ) {
    // Limit checks to this pixel's column bin, i.e. only y-coords of envelope falling in this bin 
    int colBin = px.coord.x;
    int collidePos = 0;
    
    for ( vector<coord2d_t>::const_iterator itBinVals = env[ colBin ].begin(); itBinVals != env[ colBin ].end(); ++itBinVals ) {
        if ( ( px.coord.x + 1 ) >= itBinVals->x ) {
                collidePos |= COLLIDE_RIGHT;
        }
        
        if ( ( px.coord.x - 1 ) <= itBinVals->x ) {
                collidePos |= COLLIDE_LEFT;
        }
        
        if ( ( px.coord.y + 1 ) >= itBinVals->y ) {
                collidePos |= COLLIDE_TOP;
        }
        
        if ( ( px.coord.y - 1 ) <= itBinVals->y ) {
                collidePos |= COLLIDE_BOTTOM;
        }
    }
        
    return ( collidePos );
}

// Accepts a pixel vector and reference to a 2D coordinate vector 
// comprising the collision envelope
int sprite::AddCollisionEnvCoords( vector< vector<coord2d_t> >& env, const vector<pixel>& px ) {
    for ( vector<pixel>::const_iterator itPx = px.begin(); itPx != px.end(); ++itPx ) {
        int colPos = itPx->coord.x;
        // vector<coord2d_t>::iterator itBinVal = env[ colPos ].end() - 1; // last coord in x-axis vector is always the 'largest'
        env[ colPos ].push_back( { itPx->coord } ); // add pixel coords to the appropriate coordinate vector bin
    }
    
    return ( 0 );
}