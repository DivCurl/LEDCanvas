#ifndef AN_SPLATTER_SA_H
#define	AN_SPLATTER_SA_H

#include "npAnimation.h"
#include "fft.h"

class anSplatterSA : public npAnimation {    
public:
    anSplatterSA();
    anSplatterSA( npDisplay* display, mode_t = MODE_NULL, int frames = 0, opt_t = OPT_NULL, scale_t = SCALE_1_1 );
    ~anSplatterSA();
    int Draw();   
    
private:
    float angle;  
};

#endif
