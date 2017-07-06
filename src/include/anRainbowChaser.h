#ifndef ANRAINBOWCHASER_H
#define	ANRAINBOWCHASER_H

#include "npAnimation.h"
#include "types.h"

class anRainbowChaser : public npAnimation {
public:
    anRainbowChaser();
    ~anRainbowChaser();
    anRainbowChaser( npDisplay* pDisplay, int frames, int id, mode_t mode = MODE_NONE );
    int Draw();
    int Init();
        
private:
    float angle;
    int step;       
};

#endif
