#ifndef AN_CLASSICHORIZ_SA_H
#define	AN_CLASSICHORIZ_SA_H

#include "npAnimation.h"
#include "fft.h"

class anClassicHorizSA : public npAnimation {    
public:
    anClassicHorizSA();
    anClassicHorizSA( npDisplay* display, int frames, int id, mode_t mode = MODE_NONE );
    ~anClassicHorizSA();
    int Draw();   
    int Init();
    
private:      
    float angle;  
};

#endif
