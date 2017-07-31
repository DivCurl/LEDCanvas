#ifndef SPRITE_H
#define	SPRITE_H

#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include "npAnimation.h"
#include "pixel.h"

using namespace std;

class sprite {
public:
    sprite() { }
    sprite( const sprite& copy ) : pixels( copy.pixels ), currPosition( copy.currPosition ), moving ( copy.moving ) { }
    ~sprite() { }  
    void ReplacePixels( const vector<pixel>& px );
    void PurgePixels();
    void AddPixels( const coord2d_t coord, const rgbw_t color, const uint8_t brt = 255 );
    void AddPixels( const pixel& px ); // Add single pixel to sprite
    void AddPixels( const vector<pixel>& px );  // Add vector of pixels to sprite
    vector<pixel>& GetPixelVec() { return ( pixels ); }
    void SetColor( rgbw_t color );
    void Translate( coord2d_t coord ); // translate to absolute coordinates (about sprite origin)
    void Shift( int x, int y ); // shift relative number of pixels
    void ClrColor();
    // bool CollideCheck( const vector<sprite>& targetSprites, coord2d_t testPosition );    // Loops through list of existing sprites and checks for collision
    // bool CollideCheck( sprite targetSprite, coord2d_t testPosition );           // Checks if we collide with another sprite
    // static bitset<4> CollideCheck( /* STUB */ ) {}           // Checks if we collide with another sprite
    int CollideCheck( const vector<coord2d_t>& env );    // Loops through list of existing sprites and checks for collision
    int CollideCheck( const vector<coord2d_t>& env, const pixel px );    // Loops through list of existing sprites and checks for collision
    static int CollideCheck( const vector< vector<coord2d_t> >& env, const pixel& px );    // Loops through list of existing sprites and checks for collision
    static int CollideCheck( const vector< vector<coord2d_t> >& env, const coord2d_t& coord );
    static int AddCollisionEnvCoords( vector< vector<coord2d_t> >& env, const vector<pixel>& px );
    
private:
    vector<pixel> pixels;   
    coord2d_t currPosition; // offset from definition
    bool moving;
};

#endif

