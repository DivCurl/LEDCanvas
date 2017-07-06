#ifndef AN_COLORRACE_SA_H
#define	AN_COLORRACE_SA_H

#include "npAnimation.h"
#include "fft.h"

class anColorRaceSA : public npAnimation {    
public:
    anColorRaceSA();
    anColorRaceSA( npDisplay* display, int frames, int id, mode_t mode = MODE_NONE );
    ~anColorRaceSA();
    int Draw();   
    int Init();
    
private:      
    float angle;  
};

#endif
