#ifndef AN_RAIN_H
#define	AN_RAIN_H

#include "npAnimation.h"
#include "types.h"

class anRain : public npAnimation {
public:
    anRain();
    anRain( npDisplay* pDisplay, mode_t = MODE_NONE, int frames = 0, opt_t = OPT_NONE );
    ~anRain();
    int Draw();
        
private:
    float angle;
    int step;       
};

#endif
