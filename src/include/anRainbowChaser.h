#ifndef AN_RAINBOWCHASER_H
#define	AN_RAINBOWCHASER_H

#include "npAnimation.h"
#include "types.h"

class anRainbowChaser : public npAnimation {
public:
    anRainbowChaser();
    anRainbowChaser( npDisplay* pDisplay, mode_t = MODE_NULL, int frames = 0, opt_t = OPT_NULL, scale_t = SCALE_1_1 );  
    ~anRainbowChaser();
    int Draw();
        
private:
    float angle;
    int step;       
};

#endif
