#ifndef AN_PULSEFADE_SA_H
#define	AN_PULSEFADE_SA_H

#include "npAnimation.h"
#include "fft.h"

class anPulseFadeSA : public npAnimation {    
public:
    anPulseFadeSA();
    anPulseFadeSA( npDisplay* display, int frames, int id, mode_t mode = MODE_NONE );
    ~anPulseFadeSA();
    int Draw();   
    int Init();
    
private:      
    float angle;  
};

#endif
