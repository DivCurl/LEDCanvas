#ifndef AN_PULSEFADE_SA_H
#define	AN_PULSEFADE_SA_H

#include "npAnimation.h"
#include "fft.h"

class anPulseFadeSA : public npAnimation {    
public:
    anPulseFadeSA();
    anPulseFadeSA( npDisplay* display, mode_t = MODE_NONE, int frames = 0, opt_t = OPT_NONE );
    ~anPulseFadeSA();
    int Draw();
    
private:      
    float angle;  
};

#endif
