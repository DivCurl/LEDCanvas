#ifndef AN_COMETS_H
#define	AN_COMETS_H

#include "npAnimation.h"
#include "types.h"

class anComets : public npAnimation {
public:
    anComets();
    anComets( npDisplay* pDisplay, mode_t = MODE_NULL, int frames = 0, opt_t = OPT_NULL, scale_t = SCALE_1_1 ); 
    ~anComets();
    int Draw();
        
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
