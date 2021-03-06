#ifndef AN_COLORFLOW_SA_H
#define	AN_COLORFLOW_SA_H

#include "npAnimation.h"
#include "fft.h"

class anColorFlowSA : public npAnimation {    
public:
    anColorFlowSA();
    anColorFlowSA( npDisplay* display, mode_t = MODE_NULL, int frames = 0, opt_t = OPT_NULL, scale_t = SCALE_1_1 );
    ~anColorFlowSA();
    int Draw();   
    
private:      
    float angle;  
};

#endif
