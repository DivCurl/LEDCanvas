#ifndef ANFADEMIDDLE_H
#define	ANFADEMIDDLE_H

#include "npAnimation.h"
#include "types.h"

class anFadeMiddle : public npAnimation {
public:
    anFadeMiddle();
    anFadeMiddle( npDisplay* pDisplay, mode_t = MODE_NONE, int frames = 0, opt_t = OPT_NONE );
    int Draw();
    int Init();
        
private:
    float angle;
    int step;       
};

#endif
