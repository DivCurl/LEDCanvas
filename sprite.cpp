#include "sprite.h"

using namespace std;

class sprite {
public:
    sprite();
    sprite( int numPixels );
    ~sprite();
    void Shift();
    void Show();
    void Hide();    
    
private:
    // vector<pixel> pixels;    
};