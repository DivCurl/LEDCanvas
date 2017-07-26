#ifndef AN_SPRITES_H
#define	AN_SPRITES_H

#include "npAnimation.h"
#include "types.h"

class anSprites : public npAnimation {
public:
    anSprites();
    anSprites( npDisplay* pDisplay, mode_t = MODE_NONE, int frames = 0, opt_t = OPT_NONE );
    ~anSprites();
    int Draw();
        
private:
    float angle;
};

#endif
