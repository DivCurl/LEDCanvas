#include "./include/npDisplay.h"

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
    
     if ( numLEDs > maxLED ) {
        maxLED = numLEDs;
    }
    
    // update total frame bytes
    switch ( colorMode ) {
        case RGB:
            frameBytes += maxLED * 3;           
            break;
        case RGBW:
            frameBytes += maxLED * 4;
            break;
        default:
            break;
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

int npDisplay::DeleteNeopixel( uint8_t pos ) {
    if ( neopixels.empty() ) {  // nothing yet in the container
        return ( 1 );
    } else {
        neopixels.erase( neopixels.begin() + pos );
        // update the number of connected Neopixel strips
        numNeopixels = neopixels.size();

        // update total frame bytes
        switch ( colorMode ) {
            case RGB:
                frameBytes -= maxLED * 3;           
                break;
            case RGBW:
                frameBytes -= maxLED * 4;
                break;
            default:
                break;
        }

        refreshPulses = maxLED * bytesPerPixel * 8;   
        // TODO - adjust below according to wiring orientation (future)
        rowTop = maxLED - 1;
        rowBottom = 0;
        colLeft = 0;
        colRight = numNeopixels - 1;

        return ( 0 );
    }
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

// returns packed RGB or RGBW DWORD
// color array is G-R-B[-W], returned DWORD is R-G-B[-W]
uint32_t npDisplay::GetPackedColorAtCoord( uint16_t x, uint16_t y ) {
     uint16_t index;
     uint32_t color;
    if ( ( index = GetColorArrayIndex( x, y ) ) >= 0 ) {  // returns -1 if coords are out of bounds
        if ( colorMode == RGB ) {
            color |= frameBuffer[ index ] << 8; // R
            color |= frameBuffer[ index + 1 ] << 16; // G
            color |= frameBuffer[ index + 2 ]; // B
                      
        } 
        else {
            color |= frameBuffer[ index ] << 16; // R
            color |= frameBuffer[ index + 1 ] << 24; // G
            color |= frameBuffer[ index + 2 ] << 8; // B
            color |= frameBuffer[ index + 3 ]; // W
        }
        return ( color );
    } 
} 

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
