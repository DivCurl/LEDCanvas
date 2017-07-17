#ifndef TYPES_H
#define	TYPES_H

#include <cstdint>

typedef struct {
    int x;
    int y;
} coord2d_t;

typedef struct {
    int x;
    int y;
    int z;
} coord3d_t;

typedef struct {
    bool msgPending;
    uint64_t msg;
} gModes_t;

typedef struct {
    uint8_t r;
    uint8_t g; 
    uint8_t b;
} rgb_t;

typedef struct {
    uint8_t r;
    uint8_t g; 
    uint8_t b;
    uint8_t w;
} rgbw_t;

typedef struct {
    coord2d_t coord;
    rgbw_t color;
    uint16_t brt = 255;
} pixel_t;  

typedef struct {
    coord3d_t coord;
    rgbw_t color;
    uint16_t brt = 255;
} voxel_t;  

typedef enum { 
    OPT_NONE 
} opt_t;    // Option flags

typedef enum { 
    MODE_NONE, 
    MODE_OFF, 
    MODE_STBY, 
    MODE_PAUSE, 
    MODE_REPEAT, 
    MODE_NEXT, 
    MODE_PREV, 
    MODE_STROBE, 
    MODE_FADEIN, 
    MODE_FADEOUT 
} mode_t; // Mode flags

enum { 
    FRAME_SKIP, 
    FRAME_DRAWN 
};

typedef enum { 
    RGB, 
    RGBW 
} colorMode_t;

typedef enum {
    FB_BLEND,   // blend with remnant framebuffer
    FB_CLEAR    // clear remnant framebuffer 
} fbBlendMode_t;

enum { 
    DIR_UP, 
    DIR_DOWN, 
    DIR_LEFT, 
    DIR_RIGHT, 
    DIR_MAX 
};

enum { 
    ID_AN_TEST = -1, 
    ID_AN_NONE, 
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
    ID_AN_MAX 
};

enum { 
    ORIGIN_BOTTOM_LEFT, 
    ORIGIN_BOTTOM_RIGHT, 
    ORIGIN_TOP_LEFT, 
    ORIGIN_TOP_RIGHT 
};

#endif

