#ifndef ANCOMETS_H
#define	ANCOMETS_H

#include "npAnimation.h"
#include "types.h"

class anComets : public npAnimation {
public:
    anComets();
    anComets( npDisplay* pDisplay, mode_t = MODE_NONE, int frames = 0, opt_t = OPT_NONE ); 
    int Draw();
    int Init();
        
private:
    float angle;
    int step;     
    struct comet {
        int x;
        int y;
        int dir;
        counter speed;
        rgbw_t color;
    };
    vector<comet> comets;
};

#endif
