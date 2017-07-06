#ifndef ANIMATION_H
#define	ANIMATION_H

#include <cstdint>
#include <cstring>
#include <bitset>
#include "npDisplay.h"
#include "rgbColor.h"
#include "counter.h"
#include "io.h"

using namespace std;

typedef enum { MODE_NONE, MODE_OFF, MODE_STBY, MODE_PAUSE, MODE_REPEAT, MODE_NEXT, MODE_PREV, MODE_STROBE, MODE_FADEIN, MODE_FADEOUT } mode_t;
enum { FRAME_SKIP, FRAME_DRAWN };
enum { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT, DIR_MAX };
enum { ID_AN_CHEVRONS = 1, ID_AN_COMETS, ID_AN_FADEMIDDLE, ID_AN_RAIN, ID_AN_RAINBOWCHASER, ID_AN_CLASSICHORIZ_SA, 
    ID_AN_COLORFLOW_SA, ID_AN_COLORRACE_SA, ID_AN_PULSEFADE_SA, ID_AN_SPLATTER_SA };
extern gModes_t globalMode;

class npAnimation {
public:
    npAnimation();
    npAnimation( npDisplay* pDisplay, int frames, int id, mode_t mode );
    ~npAnimation();
    virtual int Draw() = 0;
    virtual int Init() = 0;
    uint16_t GetRowBottom();
    uint16_t GetRowTop();
    uint16_t GetColLeft();
    uint16_t GetColRight();
    float Remap( float in, float inMin, float inMax, float outMin, float outMax );
    void Set( uint16_t x, uint16_t y, rgb_t color, uint16_t brt = 255 );
    void Set( uint16_t x, uint16_t y, rgbw_t color, uint16_t brt = 255 );
    void Set( rgb_t color, uint16_t brt = 255 ); // fill entire display
    void Set( rgbw_t color, uint16_t brt = 255 ); 
    void SetRow( uint16_t row, rgbw_t color, uint16_t brt = 255 );
    void SetRow( uint16_t row, uint16_t xMin, uint16_t xMax, rgbw_t color, uint16_t brt = 255 );
    void SetRowFade ( uint16_t row, float angleStart, float angleStop );
    void SetCol( uint16_t col, rgbw_t color, uint16_t brt = 255 );
    void SetCol( uint16_t col, uint16_t yMin, uint16_t yMax, rgbw_t color, uint16_t brt = 255 );
    void SetColFade( uint16_t row, float angleStart, float angleStop );
    void Clr( uint16_t x, uint16_t y );
    void Clr(); // clear entire display
    void Cpy( uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2 );
    void Mov( uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2 );
    void Swap( uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2 );
    void ClrRow( uint16_t row );
    void ClrCol( uint16_t col );
    void CpyRow( uint16_t src, uint16_t dest );
    void ShiftLeft();
    void ShiftLeft( uint16_t startCol, uint16_t endCol );
    void ShiftRight();
    void ShiftRight( uint16_t startCol, uint16_t endCol );
    void ShiftUp();
    void ShiftUp( uint16_t startRow, uint16_t endRow );
    void ShiftDown();
    void ShiftDown( uint16_t startRow, uint16_t endRow);
    void ShiftColDown( uint16_t col );
    void ShiftColUp( uint16_t col );
    void FadeOut( int fadeMode = 0, int numSteps = 1, uint16_t minBrt = 0 );
    void SetMode( mode_t mode );
    void ClrMode( mode_t mode );
    void StartDelayCounter( uint16_t delay );  // Get rid of this
    int PollGlobalModes();
    void UpdateLCD();
    void RefreshDisplay();
    bitset<16> GetModeFlags();
    uint32_t GetFrames();
    int GetID();    
        
protected:
    uint32_t frames;
    uint32_t framesDrawn;
    uint32_t cycles;
    float strobeRate = 60;
    float fadeRate;
    float dbGain = 25.f;    // good starting point
    int ret;    // return code from Draw() 
    int id;
    bool firstScan;
    bool skip;
    bitset<16> modeFlags;   
    counter ctrDelay;           // Get rid of this at some point
    npDisplay* pDisplay;
};

#endif
