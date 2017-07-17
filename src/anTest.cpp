#include "./include/anTest.h"

using namespace std;

anTest::anTest( npDisplay* pDisplay, mode_t mode, int frames, opt_t opts ) 
: npAnimation( pDisplay, mode, frames, opts ) { }

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
    
    volatile int dxBin = (float)( 64 / 2 ) / 9;
    int binCount = GetColCount(); // Just the bottom rect for now (testing) 
    vector<pixel> freqBins[ binCount ];  
    vector<pixel> pxTest[2];
    pixel pxTest2( coord2d_t { 1, 1 }, rgbwGetByAngle( 0 ) );
    asm volatile ("nop");
    
    for ( int i = 0; i < binCount; i++ ) {   
        for ( int j = 0; j <= i; j++ ) {
            freqBins[ i ].push_back( pixel( coord2d_t { i, j }, rgbwGetByAngle( 0 ) ) );       
        }
        Blit( freqBins[ i ] );
    }
    
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
                
                for ( int i = 0; i < binCount; i++ ) {   
                    freqBins[ i ].pop_back();
                    Blit( freqBins[i] );
                }
                
                RefreshDisplay( FB_BLEND );
                framesDrawn++;
            }   
        } 
    } // end main loop         
    
    return ( ret );
}