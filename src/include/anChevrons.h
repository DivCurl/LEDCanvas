#ifndef ANCHEVRONS_H
#define	ANCHEVRONS_H

#include "npAnimation.h"
#include "types.h"

class anChevrons : public npAnimation {
public:
    anChevrons();
    ~anChevrons();
    anChevrons( npDisplay* pDisplay, int frames, int id, mode_t mode = MODE_NONE );
    int Draw();
    int Init();
        
private:
    float angle;
    int step;       
};

#endif
