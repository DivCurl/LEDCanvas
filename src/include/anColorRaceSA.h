#ifndef AN_COLORRACE_SA_H
#define	AN_COLORRACE_SA_H

#include "npAnimation.h"
#include "fft.h"

class anColorRaceSA : public npAnimation {    
public:
    anColorRaceSA();
    anColorRaceSA( npDisplay* display, mode_t = MODE_NULL, int frames = 0, opt_t = OPT_NULL, scale_t = SCALE_1_1 );
    ~anColorRaceSA();
    int Draw();
    
private:      
    float angle;  
};

#endif
