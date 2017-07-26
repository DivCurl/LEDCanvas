#ifndef PIXEL_H
#define	PIXEL_H

#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include <vector>
#include "types.h"

using namespace std;

class pixel { 
public:
    pixel();
    pixel( coord2d_t coord, rgbw_t color, uint16_t brt = 255 );    
    ~pixel();
    void Shift( int x, int y, coord2d_t displayBottomLeft, coord2d_t displayTopRight );
    
    // Public to avoid having to use getters and setters for now
    coord2d_t coord { 0, 0 };
    rgbw_t color { 0, 0, 0, 0 };
    uint16_t brt = 255; // Ensures max default brightness if none specified
};

class sprite {
public:
    sprite();
    ~sprite();   
    void AddPixels( const coord2d_t coord, const rgbw_t color, const uint8_t brt = 255 );
    void AddPixels( const pixel& px );          // Add single pixel to sprite
    void AddPixels( const vector<pixel>& px );  // Add vector of pixels to sprite
    void SetColor( rgbw_t color );
    void SetMoving();
    void ClrMoving();
    void Translate( coord2d_t coord );
    bool GetMoving();
    void ClrColor();
    bool CollideCheck( const vector<sprite>& targetSprites, coord2d_t testPosition );    // Loops through list of existing sprites and checks for collision
    bool CollideCheck( sprite targetSprite, coord2d_t testPosition );           // Checks if we collide with another sprite
    
private:
    vector<pixel> pixels;   
    coord2d_t currPosition; // offset from definition
    bool moving;
};

#endif

