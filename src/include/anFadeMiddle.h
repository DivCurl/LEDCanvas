#ifndef AN_FADEMIDDLE_H
#define	AN_FADEMIDDLE_H

#include "npAnimation.h"
#include "types.h"

class anFadeMiddle : public npAnimation {
public:
    anFadeMiddle();
    anFadeMiddle( npDisplay* pDisplay, mode_t = MODE_NULL, int frames = 0, opt_t = OPT_NULL, scale_t = SCALE_1_1 );
    ~anFadeMiddle();
    int Draw();
    
private:
    float angle;
    int step;       
};

#endif
