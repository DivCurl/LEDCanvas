#include "./include/pixel.h"

using namespace std;

pixel::pixel( void ) { }

pixel::pixel( coord2d_t coord, rgbw_t color, uint16_t brt ) :  
    coord( coord ), 
    color( color ), 
    brt( brt ) { }

pixel::~pixel( void ) { }

void pixel::Shift( int x, int y, coord2d_t displayBottomLeft, coord2d_t displayTopRight ) {
    // clip coordinates to one unit outside the display limit 
    // ??? Do I really want to do it this way, or maybe just turn the pixel off after clipping to the corner? 
    if ( x < 0 ) {   // shifting left
        if ( ( coord.x - x ) < 0 ) {  // check if this shift will overflow the left extents
            color = { 0, 0, 0, 0 }; // if so, just turn the pixel off
        } else {
            coord.x -= x;
        }
    } 
    
    /* else if ( x > 0 ) { // shifting right
        if ( ( coord.x + x ) > displayTopRight.x ) {  // check if this shift will overflow the right extents
            color = { 0, 0, 0, 0 }; // if so, just turn the pixel off
        } else {
            coord.x += x;
        }
    }
     */
    
}

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

void sprite::SetMoving() {
    moving = 1;
}

void sprite::ClrMoving() {
    moving = 0;
}

bool sprite::GetMoving() {
    return ( moving );
}

// Clear the color of all pixels of the sprite
void sprite::ClrColor() {
    for ( vector<pixel>::iterator it = pixels.begin(); it != pixels.end(); it++ ) {
        (*it).color = { 0, 0, 0, 0 };
    }
}

void sprite::Translate( coord2d_t transCoord ) {
    for ( vector<pixel>::iterator it = pixels.begin(); it != pixels.end(); it++ ) {
        (*it).coord += transCoord;
        
    }
}

// Check if collision exists against a vector of sprites
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

// Check if collision exists with a single sprite
bool sprite::CollideCheck( sprite targetSprite, coord2d_t testPosition ) {
    
}