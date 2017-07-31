#include "include/anTest.h"
#include "include/matrix.h"
#include "include/types.h"

using namespace std;

anTest::anTest( npDisplay* pDisplay, mode_t mode, int frames, opt_t opts, scale_t customScaling ) 
: npAnimation( pDisplay, mode, frames, opts, customScaling ) { }

anTest::~anTest() { }

// STRICTLY FOR TESTING //
int anTest::Draw() {
    // Main animation loop
    volatile int lowerRectMidRowRef, upperRectMidRowRef, leftRectMidColRef, rightRectMidColRef;    
    
    if ( GetColCount() % 2 == 0 ) { // even number of columns
        leftRectMidColRef = floor( GetColMiddle() );
        rightRectMidColRef = ceil( GetColMiddle() );
    } else {    // odd number of columns
        leftRectMidColRef = GetColMiddle() - 1;
        rightRectMidColRef = GetColMiddle() + 1;
    }
    
    if ( GetRowCount() % 2 == 0 ) { // even number of rows
        lowerRectMidRowRef = floor( GetRowMiddle() );
        upperRectMidRowRef = ceil( GetRowMiddle() );
    } else {    // odd number of rows
        lowerRectMidRowRef = GetRowMiddle() - 1;
        upperRectMidRowRef = GetRowMiddle() + 1;
    }
    
    
    coord2d_t orig[4] = { { 2, 2}, { 2, 3}, { 2, 4}, { 2, 5} };
    coord2d_t test[4] = { 0 };
    
    
    // 
    Matrix4 mxTest, mxTest2, mxTest3;
    mxTest.Translate( 1, 1, 1 );
    mxTest2.Scale( 2, 2, 2 );
    mxTest3.RotateZ( 270 );
    
    // result[0] = m[0] * v[0] + m[4] * v[1] + m[8] * v[2] + m[12];
    //        result[1] = m[1] * v[0] + m[5] * v[1] + m[9] * v[2] + m[13];
            // result[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14];
    
    for ( int i = 0; i < 4; ++i ) {  
        test[i].x = round(mxTest3.m[0] * (float)orig[i].x) + round(mxTest3.m[4] * (float)orig[i].y);
        test[i].y = round(mxTest3.m[1] * (float)orig[i].x) + round(mxTest3.m[5] * (float)orig[i].y);
        
    }
    
    asm volatile ("nop");
       
    while ( ( framesDrawn < frames ) || modeFlags.test( MODE_REPEAT ) ) {        
        if ( !skip ) {        
            
            if ( firstScan ) { 
                firstScan = 0;              
                StartDelayCounter( 1000 );         
                ctrDelay.Reset();       
            }
    
            if ( ctrDelay.Update() ) {        
                ctrDelay.Reset(); 
                // Clr();
               
                // Blit( rotationTest );
                
                RefreshDisplay( FB_CLEAR );
                framesDrawn++;
            }   
        } 
    } // end main loop         
    
    return ( ret );
}