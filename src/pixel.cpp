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
        } 
        else {
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