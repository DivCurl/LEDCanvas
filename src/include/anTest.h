#ifndef AN_TEST_H
#define	AN_TEST_H

#include "npAnimation.h"
#include "types.h"

class anTest : public npAnimation {
public:
    anTest();
    anTest( npDisplay* pDisplay, mode_t = MODE_NULL, int frames = 0, opt_t = OPT_NULL, scale_t = SCALE_1_1 );
    ~anTest();
    int Draw();
        
private:
    float angle;
    int step;       
};

#endif
