#ifndef ANRAIN_H
#define	ANRAIN_H

#include "npAnimation.h"
#include "types.h"

class anRain : public npAnimation {
public:
    anRain();
    ~anRain();
    anRain( npDisplay* pDisplay, int frames, int id, mode_t mode = MODE_NONE );
    int Draw();
    int Init();
        
private:
    float angle;
    int step;       
};

#endif
