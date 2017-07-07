#ifndef AN_COLORRACE_SA_H
#define	AN_COLORRACE_SA_H

#include "npAnimation.h"
#include "fft.h"

class anColorRaceSA : public npAnimation {    
public:
    anColorRaceSA();
    anColorRaceSA( npDisplay* display, mode_t = MODE_NONE, int frames = 0, opt_t = OPT_NONE );
    ~anColorRaceSA();
    int Draw();   
    int Init();
    
private:      
    float angle;  
};

#endif
