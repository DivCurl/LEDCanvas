#include "npDisplay.h"

using namespace std;

npDisplay::npDisplay( void ) :
    colorMode( RGB ),                // default to RGB mode     
    globalBrightness ( 255 ),
    bytesPerPixel ( 3 ),
    rowTop( 0 ),
    rowBottom( 0 ),
    colLeft( 0 ),
    colRight( 0 ) {    
  //  frameBuffer = new uint8_t[ bytesPerPixel * 30 ]();
}

npDisplay::npDisplay( colorMode_t colorMode ) :
    colorMode( colorMode ), 
    globalBrightness ( 255 ),
    rowTop( 0 ),
    rowBottom( 0 ),
    colLeft( 0 ),
    colRight( 0 ) {    
    switch ( colorMode ) {
        case RGB:
            bytesPerPixel = 3;           
            break;
        case RGBW:
            bytesPerPixel = 4;
            break;
        default:
            break;
    }
    // frameBuffer = new uint8_t[ bytesPerPixel * 30 ]();
}

npDisplay::~npDisplay( void ) {
   // delete[] frameBuffer;
}

// Add a new Neopixel device to the container
int npDisplay::AddNeopixel( uint16_t numLEDs, volatile uint32_t* portSET, volatile uint32_t* portCLR, volatile uint32_t* portTRIS, uint16_t pin ) {
    neopixels.push_back( Neopixel( numLEDs, portSET, portCLR, portTRIS, pin ) );
    // update the number of connected Neopixel strips
    numNeopixels = neopixels.size();
    // set port TRIS mode to 0 for output on the specified pin
    *portTRIS &= ~( pin );      
    
    // update total frame bytes
    switch ( colorMode ) {
        case RGB:
            frameBytes += numLEDs * 3;           
            break;
        case RGBW:
            frameBytes += numLEDs * 4;
            break;
        default:
            break;
    }
    
    if ( numLEDs > maxLED ) {
        maxLED = numLEDs;
    }
    
//    delete[] frameBuffer;
//    frameBuffer = new uint8_t[ frameBytes ]();   
    
    refreshPulses = maxLED * bytesPerPixel * 8;   
    // TODO - adjust below according to wiring orientation (future)
    rowTop = maxLED - 1;
    rowBottom = 0;
    colLeft = 0;
    colRight = numNeopixels - 1;
    
    return ( 0 );
}

/*
// Add a new Neopixel device to the container
int npDisplay::AddNeopixel( Neopixel& np ) {
    neopixels.push_back( np );    
    // update the number of connected Neopixel strips
    numNeopixels = neopixels.size();
    // set port TRIS mode to 0 for output on the specified pin
    *np.portTRIS &= ~( np.pin );      
    
    // update total frame bytes
    switch ( colorMode ) {
        case RGB:
            frameBytes += np.numLEDs * 3;           
            break;
        case RGBW:
            frameBytes += np.numLEDs * 4;
            break;
        default:
            break;
    }
    
    // update the maximum connected LED/strip count for ports with variably-sized strips 
    if ( np.numLEDs > maxLED ) {
        maxLED = np.numLEDs;
    }
        
    refreshPulses = maxLED * bytesPerPixel * 8;    
    // TODO - adjust below according to wiring orientation (future)
    rowTop = maxLED - 1;
    rowBottom = 0;
    colLeft = 0;
    colRight = numNeopixels - 1;
   
    return ( 0 );
}
*/

// To be used for future functionality allowing resizing display size on the fly
int npDisplay::DeleteNeopixel( uint8_t pos ) {       
   
}

int npDisplay::GetColorArrayIndex( uint16_t x, uint16_t y ) {
    uint16_t height, width;
    height = maxLED;
    width = numNeopixels;
    if ( ( x > width - 1 ) || ( y > height - 1 ) ){
        return ( -1 );  // out of bounds
    }         
    return ( ( y + x * height ) * bytesPerPixel );
}
 
uint8_t npDisplay::GetMaxLED() {
    return ( maxLED );
}

uint8_t npDisplay::GetNumNeopixels() {
    return ( numNeopixels );
}

uint8_t npDisplay::GetBytesPerPixel() {
    return ( bytesPerPixel );
}

uint8_t npDisplay::GetBrightness() {
    return ( globalBrightness );
}

void npDisplay::SetBrightness( uint16_t brt ) {
    if ( brt >= 0 && brt <= 255 ) {
        globalBrightness = brt;
    }
    // update framebuffer
    for ( int i = 0; i < frameBytes; i++ ) {
        frameBuffer[ i ] = ( frameBuffer[ i ] * ( globalBrightness + 1 ) ) >> 8;            
    }
}

uint16_t npDisplay::GetFrameBytes() {
    return ( frameBytes );
}

colorMode_t npDisplay::GetColorMode () {
    return colorMode;   
}

/*
void npDisplay::SetPixel( uint16_t x, uint16_t y, rgbw_t color, uint16_t brt ) {
    uint16_t index;
    if ( ( index = GetColorArrayIndex( x, y ) ) >= 0 ) {  // returns -1 if coords are out of bounds
        frameBuffer[ index ] =   ( color.g * ( globalBrightness + 1 ) ) >> 8;
        frameBuffer[ index + 1 ] = ( color.r * ( globalBrightness + 1 ) ) >> 8;
        frameBuffer[ index + 2 ] = ( color.b * ( globalBrightness + 1 ) ) >> 8;
        frameBuffer[ index + 3 ] = ( color.w * ( globalBrightness + 1 ) ) >> 8;
    }
}
*/

void npDisplay::ClrFB() {
    memset( frameBuffer, 0, sizeof(  frameBuffer ) );
}

// returns packed RGB or RGBW dword
/*
uint32_t npDisplay::GetColorAtCoord( uint16_t x, uint16_t y ) {
     uint16_t index;
     uint32_t color;
    if ( ( index = GetColorArrayIndex( x, y ) ) >= 0 ) {  // returns -1 if coords are out of bounds
        if ( colorMode == RGB ) {
            color |= frameBuffer[ index ] << 8;
            color |= frameBuffer[ index + 1 ] << 16;
            color |= frameBuffer[ index + 2 ];
                      
        } 
        else {
            color |= frameBuffer[ index ] << 16;
            color |= frameBuffer[ index + 1 ] << 24;
            color |= frameBuffer[ index + 2 ] << 8;
            color |= frameBuffer[ index + 3 ];
        }
        return ( color );
    } 
} */

rgbw_t npDisplay::GetColorAtCoord( uint16_t x, uint16_t y ) {
    uint16_t index;
    rgbw_t tmp;
    if ( ( index = GetColorArrayIndex( x, y ) ) >= 0 ) {  // returns -1 if coords are out of bounds
        if ( colorMode == RGB ) {
            tmp.g = frameBuffer[ index ];
            tmp.r = frameBuffer[ index + 1 ];
            tmp.b = frameBuffer[ index + 2 ];
                      
        } 
        else {
            tmp.g = frameBuffer[ index ];
            tmp.r = frameBuffer[ index + 1 ];
            tmp.b = frameBuffer[ index + 2 ];
            tmp.w = frameBuffer[ index + 3 ];
            
        }
        return ( tmp );
    } 
}

void npDisplay::PushFB() {
    memcpy( frameBufferAlt, frameBuffer, sizeof( frameBufferAlt ) );
}

void npDisplay::PopFB() {
    memcpy( frameBuffer, frameBufferAlt, sizeof( frameBuffer ) );
}

uint8_t* npDisplay::GetFBPointer() {
    return frameBuffer;
}

void npDisplay::Refresh( void ) {
    memset( t1LUT, 0, sizeof( t1LUT ) );
    std::vector<Neopixel>::iterator it;
    pins = 0;
    count = 0;
    
    for ( it = neopixels.begin(); it < neopixels.end(); it++ ) {
        pins |= (*it).pin;
    }              
    // Precalculate lookup table for all ports before we enter the main loop
    // Side note: writing this loop and getting it working right was a MOTHER FUCKER!    
    for ( int pixel = 0; pixel < maxLED; pixel++  ) {                     
        for ( int bytes = 0; bytes < bytesPerPixel; bytes++ ) {
            for ( int bits = 0; bits < 8; bits++ ) { 
                for ( int port = 0; port < numNeopixels; port++ ) {                    
                    if ( !( frameBuffer[ ( pixel * bytesPerPixel ) + bytes + ( port * maxLED * bytesPerPixel ) ] & ( 1 << ( 7 - bits ) ) ) ) { 
                        t1LUT[ count ] |= ( neopixels[ port ].pin ) ;   
                    }                
                }
                count++;
            }
        }
    }
        
    INTDisableInterrupts();
    for ( int i = 0; i < refreshPulses; i++ ) {      
        LATBSET = pins;
        delay_1();          // t0 = .3us          
        LATBCLR = t1LUT[ i ]; 
        delay_2();          // t1 = .3us        
        delay_3();          // t2 = .6us
        LATBCLR = pins;
    }       
    INTEnableInterrupts();  
    
}
