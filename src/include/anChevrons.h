#ifndef AN_CHEVRONS_H
#define	AN_CHEVRONS_H

#include "npAnimation.h"
#include "types.h"

class anChevrons : public npAnimation {
public:
    anChevrons();
    anChevrons( npDisplay* pDisplay, mode_t = MODE_NULL, int frames = 0, opt_t = OPT_NULL, scale_t = SCALE_1_1 );
    ~anChevrons();
    int Draw();
        
private:
    float angle;
    int step;       
};

#endif