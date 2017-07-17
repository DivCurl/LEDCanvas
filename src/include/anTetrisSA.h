#ifndef AN_TETRIS_SA_H
#define	AN_TETRIS_SA_H

#include "npAnimation.h"
#include "types.h"

class anTetrisSA : public npAnimation {
public:
    anTetrisSA();
    anTetrisSA( npDisplay* pDisplay, mode_t = MODE_NONE, int frames = 0, opt_t = OPT_NONE );
    ~anTetrisSA();
    int Draw();
        
private:
};

#endif

