#include "./include/sprite.h"

using namespace std;

/*
sprite::sprite() { }

sprite::~sprite() { }
*/

void sprite::ReplacePixels( const vector<pixel>& px ) {
    pixels = px;    
}

void sprite::PurgePixels( ) {
    pixels.clear();
}


void sprite::AddPixels( const pixel& px ) {
    pixels.push_back( px );
}   

// Append a vector of pixels to the existing pixel vector
// Does not check for duplicates!
void sprite::AddPixels( const vector<pixel>& px ) {
    pixels.insert( std::end( pixels ), std::begin( px ), std::end( px ) );

}
// This isn't great...the extents should only be recalculated once when new pixels are added/deleted
// to or from the sprite. Works OK for small sprites composed of only a few pixels 
int sprite::GetLeftExtent() {
    vector<pixel>::iterator it = pixels.begin();
    int x = it->coord.x;
    
    for ( it = pixels.begin(); it != pixels.end(); ++it ) {
        x = ( it->coord.x < x ) ? it->coord.x : x;
    }
    
    return ( x );
}

// This isn't great...the extents should only be recalculated once when new pixels are added/deleted
// to or from the sprite. Works OK for small sprites composed of only a few pixels 
int sprite::GetRightExtent() {
    vector<pixel>::iterator it = pixels.begin();
    int x = it->coord.x;
    
    for ( it = pixels.begin(); it != pixels.end(); ++it ) {
        x = ( it->coord.x > x ) ? it->coord.x : x;
    }
    
    return ( x );
}

// This isn't great...the extents should only be recalculated once when new pixels are added/deleted
// to or from the sprite. Works OK for small sprites composed of only a few pixels 
int sprite::GetTopExtent() {
    vector<pixel>::iterator it = pixels.begin();
    int y = it->coord.y;
    
    for ( it = pixels.begin(); it != pixels.end(); ++it ) {
        y = ( it->coord.y > y ) ? it->coord.y : y;
    }
    
    return ( y );
}

// This isn't great...the extents should only be recalculated once when new pixels are added/deleted
// to or from the sprite. Works OK for small sprites composed of only a few pixels 
int sprite::GetBottomExtent() {
    vector<pixel>::iterator it = pixels.begin();
    int y = it->coord.y;
    
    for ( it = pixels.begin(); it != pixels.end(); ++it ) {
        y = ( it->coord.y < y ) ? it->coord.y : y;
    }
    
    return ( y );
}

// Set color of entire sprite
void sprite::SetColor( rgbw_t color ) {    
    for ( vector<pixel>::iterator it = pixels.begin(); it != pixels.end(); it++ ) {
        it->color = color;
    }
}

// Clear the color of all pixels of the sprite
void sprite::ClrColor() {
    for ( vector<pixel>::iterator it = pixels.begin(); it != pixels.end(); it++ ) {
        it->color = { 0, 0, 0, 0 };
    }
}

void sprite::Translate( coord2d_t transCoord ) {
    // The first pixel is the anchor of the sprite.
    vector<pixel>::iterator it = pixels.begin();
    coord2d_t newOrigin;
    newOrigin.x = transCoord.x - it->coord.x;
    newOrigin.y = transCoord.y - it->coord.y;
    
    for ( ; it != pixels.end(); it++ ) {
        it->coord += newOrigin;
        
    }
}

void sprite::Shift( int x, int y ) {
    for ( vector<pixel>::iterator it = pixels.begin(); it != pixels.end(); ++it ) {
        it->coord.x += x;
        it->coord.y += y;        
    }
}

// Per-pixel collision detection
int sprite::CollideCheck( const vector< vector<coord2d_t> >& env, const pixel& px ) {
    // Limit checks to this pixel's column bin, i.e. only y-coords of envelope falling in this bin 
    int colBin = px.coord.x;
    int collidePos = 0;
    
    for ( vector<coord2d_t>::const_iterator itBinVals = env[ colBin ].begin(); itBinVals != env[ colBin ].end(); ++itBinVals ) {
        if ( /* ( ( px.coord.x + 1 ) >= itBinVals->x ) || */ ( px.coord.x  > 8 ) ) {
            collidePos |= COLLIDE_RIGHT;
        }
        
        if ( /* ( ( px.coord.x - 1 ) <= itBinVals->x ) || */ ( px.coord.x < 0 ) ) {
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

// Per-pixel collision detection
int sprite::CollideCheck( const vector< vector<coord2d_t> >& env, const coord2d_t& coord ) {
    // Limit checks to this pixel's column bin, i.e. only y-coords of envelope falling in this bin 
    int colBin = coord.x;
    int collidePos = 0;
    
    if ( ( coord.x > 8 ) ) {
        collidePos |= COLLIDE_RIGHT;
    }
    
    if ( ( coord.x < 0 ) ) {
        collidePos |= COLLIDE_LEFT;
    }
    
    for ( vector<coord2d_t>::const_iterator itBinVals = env[ colBin ].begin(); itBinVals != env[ colBin ].end(); ++itBinVals ) {
        if ( ( coord.y == itBinVals->y ) && ( coord.x == itBinVals->x ) ) {
            collidePos |= COLLIDE_RIGHT | COLLIDE_LEFT; // need to fix
        }
        
        if ( coord.y >= itBinVals->y ) {
            collidePos |= COLLIDE_TOP;
        }

        if ( coord.y <= itBinVals->y ) {
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
        // vector<coord2d_t>::iterator itBinVal = envComp[ colPos ].end() - 1; // last coord in x-axis vector is always the 'largest'
        env[ colPos ].push_back( { itPx->coord } ); // add pixel coords to the appropriate coordinate vector bin
    }
    
    return ( 0 );
}