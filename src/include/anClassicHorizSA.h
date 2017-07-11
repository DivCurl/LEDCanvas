#ifndef AN_CLASSICHORIZ_SA_H
#define	AN_CLASSICHORIZ_SA_H

#include "npAnimation.h"
#include "fft.h"

class anClassicHorizSA : public npAnimation {    
public:
    anClassicHorizSA();
    anClassicHorizSA( npDisplay* display, mode_t = MODE_NONE, int frames = 0, opt_t = OPT_NONE );
    int Draw();   
    int Init();
    
private:      
    float angle;  
};

#endif
