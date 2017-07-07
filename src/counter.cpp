#include "./include/counter.h"

using namespace std;

counter::counter( void ) { }

counter::counter( uint16_t delay ) : pre ( delay ) { }

counter::~counter( void ) { }

void counter::Start() {
    if ( !en ) {
        // only if not already enabled...
        en = 1;
        startTicks = t2Ticks;
    }    
}

void counter::Start( uint16_t delay ) {
    // only if not already enabled...
    if ( !en ) {
        en = 1;
        pre = delay;
        startTicks = t2Ticks;
    }
}

bool counter::Update() {
    if ( !dn ) {
        // update accumulator
        if ( t2Ticks < startTicks ) {     // timer has overflowed since last update
            acc = ( numeric_limits<uint32_t>::max() - startTicks ) + t2Ticks;
        } else {
            acc = t2Ticks - startTicks;   // no overflow; update tick accumulator
        }
        if ( acc >= pre ) { // we've hit the preset
            dn = 1;
            return ( 1 );
        } else {
            return ( 0 );
        }
    } else {
        // already done; waiting for reset
        return ( 0 );
    }
}

// void counter::Pause() {}

// void counter::Resume()  {}

void counter::Stop() {
    acc = 0;
    en = 0;
    dn = 0;
}


void counter::SetDelay( uint16_t delay ) {
    pre = delay;    
}

uint16_t counter::GetDelay() {
    return ( pre );
}

void counter::Reset() {
    acc = 0;
    en = 0;
    dn = 0;
    Start();
}         
