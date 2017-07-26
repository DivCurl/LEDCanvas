#ifndef AN_TETRIS_SA_H
#define	AN_TETRIS_SA_H

#include "npAnimation.h"
#include "types.h"

using namespace std;

enum { O, L, Z, T, I };
const int MAX_PIECES = 5;
const int MAX_ROTATIONS = 4;

class anTetrisSA : public npAnimation {
public:
    anTetrisSA();
    anTetrisSA( npDisplay* pDisplay, mode_t = MODE_NONE, int frames = 0, opt_t = OPT_NONE );
    ~anTetrisSA();
    int Draw();
    bool SpawnBlock();
        
private:
    vector<sprite> blocks;
    bool noMoves;
};

#endif

