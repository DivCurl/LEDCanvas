#ifndef ANSTROBES_H
#define	ANSTROBES_H

#include "npAnimation.h"
#include "types.h"

enum { ID_STROBE_BASIC, ID_STROBE_CHASER, ID_STROBE_TO_MIDDLE, ID_STROBE_MAX };
// extern gModes_t globalModes;

class anStrobes : public npAnimation {
public:
    anStrobes();
    ~anStrobes();
    anStrobes( npDisplay* pDisplay, int frames, int id, mode_t mode = MODE_NONE );
    int Draw();
    int Init();
    bool StrobeBasic();     // Done
    bool StrobeChaser();    // TODO
    bool StrobeToMiddle();  // TODO  
        
private:   
    float angle;
    float strobeRate = 50;
}; 

#endif

