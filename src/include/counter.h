#ifndef TIMER_H
#define	TIMER_H

#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include <cstdlib>
#include <cstdint>
#include <limits>
#include <plib.h>  
#include "types.h"

extern volatile uint32_t t2Ticks;
extern uint16_t T2Period;

class counter {
public:
    counter(); 
    counter( uint16_t delay, bool startMode = OFF ); 
    ~counter();
    void Start();
    void Start( uint16_t delay );
    bool Update();
    bool Done();
    void Pause();
    void Resume();
    void Stop();
    void SetDelay( uint16_t delay );
    uint16_t GetDelay();
    void Reset();
    void Reset( uint16_t delay );
    
private:
    uint32_t acc = 0;
    uint32_t pre = 0;
    uint32_t startTicks = 0;
    bool en = 0;
    bool dn = 0;   
};

#endif

