#ifndef RGBCOLOR_H
#define	RGBCOLOR_H

#include <cstdint>
#include <cmath>
#include "types.h"

#define RGB_RED             0
#define RGB_ORANGE          30
#define RGB_YELLOW          60
#define RGB_SPRING_GREEN    90
#define RGB_GREEN           120
#define RGB_CYAN            180
#define RGB_BLUE            240
#define RGB_VIOLET          270
#define RGB_MAGENTA         300

rgb_t rgbGetByAngle( float angle );
rgbw_t rgbwGetByAngle( float angle, uint8_t whiteTemp = 0 );

#endif
