#ifndef AN_TETRIS_SA_H
#define	AN_TETRIS_SA_H

#include "npAnimation.h"
#include "types.h"
#include "fft.h"

const int MAX_PIECES = 7;
const int MAX_ROTATIONS = 4;
using namespace std;

class anTetrisSA : public npAnimation {
public:
    anTetrisSA();
    anTetrisSA( npDisplay* pDisplay, mode_t = MODE_NULL, int frames = 0, opt_t = OPT_NULL, scale_t = SCALE_1_1 );
    ~anTetrisSA();
    int Draw();
    bool SpawnBlock( float dispCenter, int block );
        
private:
    vector<sprite> blocks;
    bool gameOver = 0;
    bool blockMoving = 0;
    int vertShifts = 0;
    rgbw_t blockColors[ MAX_PIECES ];
    
};  

#endif

