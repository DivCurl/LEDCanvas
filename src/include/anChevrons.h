#ifndef AN_CHEVRONS_H
#define	AN_CHEVRONS_H

#include "npAnimation.h"
#include "types.h"

class anChevrons : public npAnimation {
public:
    anChevrons();
    anChevrons( npDisplay* pDisplay, mode_t = MODE_NONE, int frames = 0, opt_t = OPT_NONE );
    ~anChevrons();
    int Draw();
        
private:
    float angle;
    int step;       
};

#endif