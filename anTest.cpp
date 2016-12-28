#include "anTest.h"

using namespace std;

anTest::anTest( npDisplay* pDisplay, int frames, int id = ID_NONE, mode_t mode = MODE_NONE ) 
: npAnimation( pDisplay, frames, id, mode ) {
}

anTest::~anTest() {    
    
}

// Exists purely for testing shit...
int anTest::Draw() {    
    Clr();
    // x = x_0 + v_0*t + 1/2*at^2
    ret = 0;

    vector<counter> counters(9);
    vector<counter>::iterator it;
    
    
    // Set up some pixels to start with
    Set(0, 0, rgbwGetByAngle(0, 0));
    Set(1, 0, rgbwGetByAngle(39, 0));
    Set(2, 0, rgbwGetByAngle(79, 0));
    Set(3, 0, rgbwGetByAngle(119, 0));
    Set(4, 0, rgbwGetByAngle(159, 0));
    Set(5, 0, rgbwGetByAngle(199, 0));
    Set(6, 0, rgbwGetByAngle(239, 0));
    Set(7, 0, rgbwGetByAngle(279, 0));
    Set(8, 0, rgbwGetByAngle(319, 0));

    int i = 1;
    for ( it = counters.begin(); it < counters.end(); it++ ) {        
        (*it).Start(i*50);
        i++;
    }
    
    while ( ( framesDrawn < frames || modeFlags.test( MODE_REPEAT ) ) ) {
        i = 0;
        for ( it = counters.begin(); it < counters.end(); it++ ) {
            if ( (*it).Update() ) {
                ShiftColUp(i);
                (*it).Reset();
            }
            i++;
        }
        
        RefreshDisplay();
    }

    return ( ret );    
}

int anTest::Init() { 

}
 
 