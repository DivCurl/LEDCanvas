#ifndef SPRITE_H
#define	SPRITE_H

#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include "npAnimation.h"
#include "pixel.h"
#include "matrix.h"

using namespace std;

class sprite {
public:
    sprite() { }
    sprite( const vector<pixel>& px ) : pixels( px ) { }
    sprite( const sprite& copy ) : pixels( copy.pixels ) { }
    ~sprite() { }  
    void ReplacePixels( const vector<pixel>& px );
    void PurgePixels();
    void AddPixels( const coord2d_t coord, const rgbw_t color, const uint8_t brt = 255 );
    void AddPixels( const pixel& px ); // Add single pixel to sprite
    void AddPixels( const vector<pixel>& px );  // Add vector of pixels to sprite
    vector<pixel>& GetPixelVec() { return ( pixels ); }
    int GetLeftExtent();
    int GetRightExtent();
    int GetBottomExtent();
    int GetTopExtent();
    void SetColor( rgbw_t color );
    void Translate( coord2d_t coord ); // translate to absolute coordinates (about sprite origin)
    void Shift( int x, int y ); // shift relative number of pixels
    void ClrColor();
    int CollideCheck( const vector<coord2d_t>& env );    // Loops through list of existing sprites and checks for collision
    int CollideCheck( const vector<coord2d_t>& env, const pixel px );    // Loops through list of existing sprites and checks for collision
    static int CollideCheck( const vector< vector<coord2d_t> >& env, const pixel& px );    // Loops through list of existing sprites and checks for collision
    static int CollideCheck( const vector< vector<coord2d_t> >& env, const coord2d_t& coord );
    static int AddCollisionEnvCoords( vector< vector<coord2d_t> >& env, const vector<pixel>& px );
    
    
private:
    vector<pixel> pixels;   
};

#endif

