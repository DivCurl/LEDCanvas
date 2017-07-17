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
    if ( !en ) {
        return ( 0 );
    } else if ( en && !dn ) {
        // update accumulator
        if ( t2Ticks < startTicks ) {     // overflow
            acc = ( numeric_limits<uint32_t>::max() - startTicks ) + t2Ticks;
        } else {
            acc = t2Ticks - startTicks;   // no overflow
        }
        // check for done status
        if ( acc >= pre ) {
            dn = 1;
            return ( 1 );
        } else {
            return ( 0 );
        }
    } else {        
        return ( 0 );
    }
}

bool counter::Done() {
    Update();
    return ( dn );
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

void counter::Reset( uint16_t delay ) {
    SetDelay( delay );
    acc = 0;
    en = 0;
    dn = 0;
    Start();
}  
