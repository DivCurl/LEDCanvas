#ifndef PIXEL_H
#define	PIXEL_H

#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include "types.h"

class pixel { 
public:
    pixel();
    pixel( coord2d_t coord, rgbw_t color, uint16_t brt = 255 );    
    ~pixel();
    void Shift( int x, int y, coord2d_t displayBottomLeft, coord2d_t displayTopRight );
    
    coord2d_t coord { -1, -1 };
    rgbw_t color;
    uint16_t brt = 255; // Ensures max default brightness if none specified
};

#endif

