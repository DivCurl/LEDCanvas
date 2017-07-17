#ifndef AN_RAINBOWCHASER_H
#define	AN_RAINBOWCHASER_H

#include "npAnimation.h"
#include "types.h"

class anRainbowChaser : public npAnimation {
public:
    anRainbowChaser();
    anRainbowChaser( npDisplay* pDisplay, mode_t = MODE_NONE, int frames = 0, opt_t = OPT_NONE );  
    ~anRainbowChaser();
    int Draw();
        
private:
    float angle;
    int step;       
};

#endif
