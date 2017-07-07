#include "./include/Neopixel.h"

using namespace std;

Neopixel::Neopixel( void ) { }

Neopixel::Neopixel( uint16_t numLEDs, volatile uint32_t* portSET, volatile uint32_t* portCLR, volatile uint32_t* portTRIS, uint16_t pinLED ) : 
    numLEDs( numLEDs ), 
    pin( pinLED ), 
    pinMask ( pin ),
    portSET ( portSET ),
    portCLR( portCLR ),
    portTRIS( portTRIS ) {
}
    
Neopixel::~Neopixel() { }
