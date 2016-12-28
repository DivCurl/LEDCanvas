#ifndef ANPATTERNS_H
#define	ANPATTERNS_H

#include "npAnimation.h"
#include "types.h"

enum { ID_PATTERN_RAINBOW_1, ID_PATTERN_RAIN, ID_PATTERN_FADE_MIDDLE, ID_PATTERN_RANDOM_FILL, ID_PATTERN_CHEVRONS, ID_PATTERN_COMETS, ID_PATTERN_FIREWORKS, ID_PATTERN_MAX };

class anPatterns : public npAnimation {
public:
    anPatterns();
    ~anPatterns();
    anPatterns( npDisplay* pDisplay, int frames, int id, mode_t mode = MODE_NONE );
    int Draw();
    int Init();
    bool RainbowChaser1();  // Done
    bool Rain();            // Done
    bool FadeToMiddle();    // Done
    bool Firefly();         // Done    
    bool RandomFill();      // Done
    bool StackedChevrons(); // Done
    bool Comets();          // Done
    bool FireWorks();       // Test
    bool ChaseOpposites();  // TODO    
    bool Snake();           // TODO
        
private:
    float angle;
    int step;       
    
    struct flySaucer {
        int x;
        int y;
        int dir;
        counter speed;
        rgbw_t color;
    };
    
    struct fireWork {
        int x, y, yExplode;     
        rgbw_t particleColor;
        vector<coord> particles;
        vector<coord> delta;        
        counter dropSpeed;       
        counter launchSpeed;
    } fireWorks;
    
    
    vector<flySaucer> saucers;
};

#endif
