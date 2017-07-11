#ifndef ANRAINBOWCHASER_H
#define	ANRAINBOWCHASER_H

#include "npAnimation.h"
#include "types.h"

class anRainbowChaser : public npAnimation {
public:
    anRainbowChaser();
    anRainbowChaser( npDisplay* pDisplay, mode_t = MODE_NONE, int frames = 0, opt_t = OPT_NONE );  
    int Draw();
    int Init();
        
private:
    float angle;
    int step;       
};

#endif
