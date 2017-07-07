#include "./include/rgbColor.h"

using namespace std;

rgbw_t rgbwGetByAngle( float angle, uint8_t whiteTemp ) {
    if ( whiteTemp == 255 ) {   // only if white color is max
        return ( rgbw_t { 0, 0, 0, 255 } );
    }
    
    uint8_t r, g, b;
    // double angle = fmod( inAngle, 360 );
    while ( angle >= 360.0f ) {
        angle -= 360.0f;
    }
    // 0 deg = 255, 0 0
    // 60 deg = 255, 255, 0
    // 120 deg = 0, 255, 0
    // 180 deg = 0, 255, 255
    // 240 deg = 0, 0 255
    // 300 deg = 255, 0, 255
    // delta-x = 255   
    
    // increase g value, hold red at max
    if ( ( angle >= 0 ) && ( angle < 60 ) ) {
        r = 255.f;
        g = ( angle * 4.25 );
        b = 0.f;
        return ( rgbw_t { r, g, b, whiteTemp } );
    }

    // decrease red value, hold g at max
    if ( ( angle >= 60 ) && ( angle < 120 ) ) {
        r = ( 255 - (angle-60) * 4.25 );
        g = 255.f;
        b = 0.f;
        return ( rgbw_t { r, g, b, whiteTemp } );
    }

    // increase blue value, hold g at max
    if ( ( angle >= 120 ) && ( angle < 180 ) ) {
        r = 0.f;
        g = 255.f;
        b = ( (angle-120) * 4.25 );
        return ( rgbw_t { r, g, b, whiteTemp } );
    }

    // decrease G value, hold B at max
    if ( ( angle >= 180 ) && ( angle < 240 ) ) {
        r = 0.f;
        g = ( 255 - (angle-180) * 4.25 );
        b = 255.f;
        return ( rgbw_t { r, g, b, whiteTemp } );
    }

    // increase R value, hold B at max
    if ( ( angle >= 240 ) && ( angle < 300 ) ) {
        r = ( (angle-240) * 4.25 );
        g = 0.f;
        b = 255.f;
        return ( rgbw_t { r, g, b, whiteTemp } );
    }

    // decrease B value, hold R at max
    if ( ( angle >= 300 ) && ( angle < 360 ) ) {
        r = 255.f;
        g = 0.f;
        b = ( 255 - (angle-300) * 4.25 );
        return ( rgbw_t { r, g, b, whiteTemp } );
    }  
}
 