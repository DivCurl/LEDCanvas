#ifndef ANFADEMIDDLE_H
#define	ANFADEMIDDLE_H

#include "npAnimation.h"
#include "types.h"

class anFadeMiddle : public npAnimation {
public:
    anFadeMiddle();
    ~anFadeMiddle();
    anFadeMiddle( npDisplay* pDisplay, int frames, int id, mode_t mode = MODE_NONE );
    int Draw();
    int Init();
        
private:
    float angle;
    int step;       
};

#endif
