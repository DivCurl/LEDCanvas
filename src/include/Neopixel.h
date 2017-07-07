#ifndef Neopixel_H
#define Neopixel_H

#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include <cstdint>
#include <cstdlib>
#include <p32xxxx.h>
#include <plib.h>    

class Neopixel {    
friend class npDisplay;

public:
    Neopixel( void );
	Neopixel( uint16_t numLEDs, volatile uint32_t* portSET, volatile uint32_t* portCLR, volatile uint32_t* portTRIS, uint16_t pin  );	
	~Neopixel( void );
      
private:
    uint16_t pin;
	volatile uint32_t *portSET;
	volatile uint32_t *portCLR;
    volatile uint32_t *portTRIS;
	uint16_t pinMask;
    uint16_t numLEDs;    
    uint16_t byteCount;	        
};

#endif