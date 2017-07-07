#ifndef TYPES_H
#define	TYPES_H

#include <cstdint>

struct coord {
    int x;
    int y;
    int z;
};

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

typedef enum { MODE_NONE, MODE_OFF, MODE_STBY, MODE_PAUSE, MODE_REPEAT, MODE_NEXT, MODE_PREV, MODE_STROBE, MODE_FADEIN, MODE_FADEOUT } mode_t; // Mode flags
typedef enum { OPT_NONE } opt_t;    // Option flags
enum { FRAME_SKIP, FRAME_DRAWN };
enum { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT, DIR_MAX };
enum { ID_AN_CHEVRONS = 1, ID_AN_COMETS, ID_AN_FADEMIDDLE, ID_AN_RAIN, ID_AN_RAINBOWCHASER, ID_AN_CLASSICHORIZ_SA, 
    ID_AN_COLORFLOW_SA, ID_AN_COLORRACE_SA, ID_AN_PULSEFADE_SA, ID_AN_SPLATTER_SA };

#endif

