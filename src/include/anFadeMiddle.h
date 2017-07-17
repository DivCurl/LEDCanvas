#ifndef AN_FADEMIDDLE_H
#define	AN_FADEMIDDLE_H

#include "npAnimation.h"
#include "types.h"

class anFadeMiddle : public npAnimation {
public:
    anFadeMiddle();
    anFadeMiddle( npDisplay* pDisplay, mode_t = MODE_NONE, int frames = 0, opt_t = OPT_NONE );
    ~anFadeMiddle();
    int Draw();
    
private:
    float angle;
    int step;       
};

#endif
