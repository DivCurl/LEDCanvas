#ifndef AN_SPLATTER_SA_H
#define	AN_SPLATTER_SA_H

#include "npAnimation.h"
#include "fft.h"

class anSplatterSA : public npAnimation {    
public:
    anSplatterSA();
    anSplatterSA( npDisplay* display, mode_t = MODE_NONE, int frames = 0, opt_t = OPT_NONE );
    ~anSplatterSA();
    int Draw();   
    
private:
    float angle;  
};

#endif
