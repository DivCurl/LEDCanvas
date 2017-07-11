#ifndef ANRAIN_H
#define	ANRAIN_H

#include "npAnimation.h"
#include "types.h"

class anRain : public npAnimation {
public:
    anRain();
    anRain( npDisplay* pDisplay, mode_t = MODE_NONE, int frames = 0, opt_t = OPT_NONE );
    int Draw();
    int Init();
        
private:
    float angle;
    int step;       
};

#endif
