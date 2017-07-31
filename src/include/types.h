#ifndef TYPES_H
#define	TYPES_H

#include <cstdint>

#define PI 3.141592654f
#define PI_OVER_180 ( PI / 180.0f )

struct coord2d_t {
    int x;
    int y;
    
    coord2d_t( int x = 0, int y = 0 ) : x( x ), y( y ) { }
    
    coord2d_t& operator=( const coord2d_t& coord ) {
        x = coord.x;
        y = coord.y;
        return ( *this );
    }   
    
    coord2d_t& operator+=( const coord2d_t& coord ) {
        x += coord.x;
        y += coord.y;
        return ( *this );
    }
    
    coord2d_t& operator++() {
        x++;
        y++;
        return ( *this );
    }
    
    coord2d_t& operator--() {
        x--;
        y--;
        return ( *this );
    }
    
    coord2d_t& operator-=( const coord2d_t& coord ) {
        x -= coord.x;
        y -= coord.y;
        return ( *this );
    }

    coord2d_t operator+( const coord2d_t& coord ) const {
        return coord2d_t( coord.x + x, coord.y + y );
    }
    
    coord2d_t operator-( const coord2d_t& coord ) const {
        return coord2d_t( coord.x - x, coord.y - y );
    }

    bool operator==( const coord2d_t& coord ) const {
        return ( x == coord.x && y == coord.y );
    }
    
    bool operator>( const coord2d_t& coord ) const {
        return ( x > coord.x && y > coord.y );
    }
    
    bool operator>=( const coord2d_t& coord ) const {
        return ( x >= coord.x && y >= coord.y );
    }
    
    bool operator<=( const coord2d_t& coord ) const {
        return ( x <= coord.x && y <= coord.y );
    }
}; 

struct gModes_t {
    bool msgPending;
    uint64_t msg;
};

struct rgb_t {
    uint8_t r;
    uint8_t g; 
    uint8_t b;
};

struct rgbw_t {
    uint8_t r;
    uint8_t g; 
    uint8_t b;
    uint8_t w;
};

enum opt_t { 
    OPT_NULL,
    OPT_CUSTOM_SCALE
};    // Option flags

enum mode_t { 
    MODE_NULL, 
    MODE_OFF,       // Force all pixels to off 
    MODE_STBY, 
    MODE_PAUSE,     
    MODE_REPEAT, 
    MODE_NEXT, 
    MODE_PREV, 
    MODE_STROBE, 
    MODE_FADEIN, 
    MODE_FADEOUT 
}; // Mode flags

enum scale_t { 
    SCALE_1_1,
    SCALE_1_2,
    SCALE_1_3,
    SCALE_1_4,
    SCALE_1_5,
    SCALE_1_6,
    SCALE_1_7,
    SCALE_1_8,
    SCALE_1_9,
    SCALE_1_10
};

enum { 
    FRAME_SKIP, 
    FRAME_DRAWN 
};

enum colorMode_t { 
    RGB, 
    RGBW 
};

enum fbBlendMode_t {
    FB_BLEND,   // blend with remnant framebuffer
    FB_CLEAR    // clear remnant framebuffer 
};

enum { 
    DIR_UP, 
    DIR_DOWN, 
    DIR_LEFT, 
    DIR_RIGHT, 
    DIR_MAX 
};

enum { 
    OFF,
    ON
};

enum { 
    ID_AN_TEST = -1, 
    ID_AN_NULL, 
    ID_AN_CHEVRONS, 
    ID_AN_COMETS, 
    ID_AN_FADEMIDDLE, 
    ID_AN_RAIN, 
    ID_AN_RAINBOWCHASER, 
    ID_AN_SPRITES,
    ID_AN_CLASSIC_SA, 
    ID_AN_COLORFLOW_SA, 
    ID_AN_COLORRACE_SA, 
    ID_AN_PULSEFADE_SA, 
    ID_AN_SPLATTER_SA, 
    ID_AN_TETRIS_SA, 
    ID_AN_MAX 
};

enum { 
    ORIGIN_BOTTOM_LEFT, 
    ORIGIN_BOTTOM_RIGHT, 
    ORIGIN_TOP_LEFT, 
    ORIGIN_TOP_RIGHT 
};

enum { 
    COLLIDE_NULL = 0x00,
    COLLIDE_RIGHT = 0x01,
    COLLIDE_TOP = 0x02,
    COLLIDE_LEFT = 0x04,
    COLLIDE_BOTTOM = 0x08
};

#endif

