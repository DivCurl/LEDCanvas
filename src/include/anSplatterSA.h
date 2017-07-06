#ifndef AN_SPLATTER_SA_H
#define	AN_SPLATTER_SA_H

#include "npAnimation.h"
#include "fft.h"

class anSplatterSA : public npAnimation {    
public:
    anSplatterSA();
    anSplatterSA( npDisplay* display, int frames, int id, mode_t mode = MODE_NONE );
    ~anSplatterSA();
    int Draw();   
    int Init();
    
private:
    float angle;  
};

#endif
