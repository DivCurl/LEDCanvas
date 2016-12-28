#ifndef ANTEST_H
#define	ANTEST_H

#include "npAnimation.h"

enum { ID_NONE };
// extern gModes_t globalModes;

class anTest : public npAnimation {
public:
    anTest();
    ~anTest();
    anTest( npDisplay* pDisplay, int frames, int id, mode_t mode );
    int Draw();
    int Init();
        
private:   
    float angle = 0;
    uint16_t count = 0;            
}; 

#endif
