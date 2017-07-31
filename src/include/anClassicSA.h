#ifndef AN_CLASSIC_SA_H
#define	AN_CLASSIC_SA_H

#include "npAnimation.h"
#include "fft.h"

class anClassicSA : public npAnimation {    
public:
    anClassicSA();
    anClassicSA( npDisplay* display, mode_t = MODE_NULL, int frames = 0, opt_t = OPT_NULL, scale_t = SCALE_1_1 );
    ~anClassicSA();
    int Draw();   
    
private:      
    float angle;    
};

#endif
