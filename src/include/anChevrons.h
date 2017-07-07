#ifndef ANCHEVRONS_H
#define	ANCHEVRONS_H

#include "npAnimation.h"
#include "types.h"

class anChevrons : public npAnimation {
public:
    anChevrons();
    anChevrons( npDisplay* pDisplay, mode_t = MODE_NONE, int frames = 0, opt_t = OPT_NONE );
    ~anChevrons();
    int Draw();
    int Init();
        
private:
    float angle;
    int step;       
};

#endif
