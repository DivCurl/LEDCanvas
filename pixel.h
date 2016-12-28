#ifndef PIXEL_H
#define	PIXEL_H

#include "types.h"
#include "rgbColor.h"

class pixel {
public:
    void Set( coord );
    void Clr( coord );
    void Mov( coord c1, coord c2 );
    void Cop( coord c1, coord c2 );
    coord GetCoord();    
    
private:
    coord pCoord;
    rgbw_t color;
    int brt;
};


#endif

