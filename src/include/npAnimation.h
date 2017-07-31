#ifndef ANIMATION_H
#define	ANIMATION_H

#include <cstdint>
#include <cstring>
#include <bitset>
#include <vector>
#include <array>
#include "npDisplay.h"
#include "rgbColor.h"
#include "pixel.h"
#include "sprite.h"
#include "counter.h"
#include "io.h"
#include "types.h"

using namespace std;
extern gModes_t globalMode;

class npAnimation {
    
public:
    npAnimation();
    npAnimation( npDisplay* pDisplay, mode_t mode, int frames, opt_t opts, scale_t customScale );
    virtual ~npAnimation(); 
    virtual int Draw() = 0;
    uint16_t GetRowBottom();
    uint16_t GetRowTop();
    uint16_t GetColLeft();
    uint16_t GetColRight();
    uint16_t GetRowCount();
    uint16_t GetColCount();
    float GetDisplayCenter();
    coord2d_t GetDisplayBottomLeftCoord();
    coord2d_t GetDisplayTopRightCoord();
    float GetRowMiddle();
    float GetColMiddle();
    void SetScaling();
    float Remap( float in, float inMin, float inMax, float outMin, float outMax );
    void Set( uint16_t x, uint16_t y, rgb_t color, uint16_t brt = 255 );
    void Set( uint16_t x, uint16_t y, rgbw_t color, uint16_t brt = 255 );
    void Set( rgb_t color, uint16_t brt = 255 ); // fill entire display
    void Set( rgbw_t color, uint16_t brt = 255 ); 
    void Set( const pixel& px );
    void SetRow( uint16_t row, rgbw_t color, uint16_t brt = 255 );
    void SetRow( uint16_t row, uint16_t xMin, uint16_t xMax, rgbw_t color, uint16_t brt = 255 );
    void SetRowFade ( uint16_t row, float angleStart, float angleStop );
    void SetCol( uint16_t col, rgbw_t color, uint16_t brt = 255 );
    void SetCol( uint16_t col, uint16_t yMin, uint16_t yMax, rgbw_t color, uint16_t brt = 255 );
    void SetColFade( uint16_t row, float angleStart, float angleStop );
    void Clr( uint16_t x, uint16_t y ); // clear single pixel
    void Clr(); // clear entire display
    void Cpy( uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2 );
    void Mov( uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2 );
    void Swap( uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2 );
    void Blit( const vector<pixel>& px );   
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
    void ShiftPixels( vector<pixel>& px, coord2d_t offset );
    void FadeOut( int fadeMode = 0, int numSteps = 1, uint16_t minBrt = 0 );
    void SetMode( mode_t mode );
    void ClrMode( mode_t mode );
    void StartDelayCounter( uint16_t delay );  // Get rid of this
    int PollGlobalModes();
    void UpdateLCD();
    void RefreshDisplay( fbBlendMode_t blendMode = FB_BLEND );
    bitset<16> GetModeFlags();
    uint32_t GetFrames();
    int GetID();    
        
protected:
    uint32_t frames;
    uint32_t framesDrawn;    
    scale_t customScale;
    coord2d_t xyScale = { 1, 1 };
    float fadeRate;
    float dbGain = 25.f;    // good starting point
    int ret;    // return code from Draw() 
    int id;
    bool firstScan;
    bool skip;
    bitset<16> modeFlags;   
    bitset<16> optFlags;   
    counter ctrDelay;           // Get rid of this at some point
    npDisplay* pDisplay;
};

#endif
