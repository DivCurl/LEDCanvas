#ifndef AN_COLORFLOW_SA_H
#define	AN_COLORFLOW_SA_H

#include "npAnimation.h"
#include "fft.h"

class anColorFlowSA : public npAnimation {    
public:
    anColorFlowSA();
    anColorFlowSA( npDisplay* display, int frames, int id, mode_t mode = MODE_NONE );
    ~anColorFlowSA();
    int Draw();   
    int Init();
    
private:      
    float angle;  
};

#endif
