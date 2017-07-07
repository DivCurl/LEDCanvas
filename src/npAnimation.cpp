#include "./include/npAnimation.h"  

using namespace std;

npAnimation::npAnimation() :
    firstScan( 1 ),
    pDisplay( NULL ),
    frames( 0 ) {
        optFlags.set ( OPT_NONE );
        modeFlags.set( MODE_NONE ); 
} 

npAnimation::npAnimation( npDisplay* pDisplay, mode_t mode, int frames, opt_t opts ) : 
    firstScan( 1 ),
    pDisplay ( pDisplay ),
    frames( frames ) {
        optFlags.set ( opts );
        modeFlags.set( mode ); 
}

npAnimation::~npAnimation() { }

void npAnimation::SetMode( mode_t mode ) {
    modeFlags.set( mode );
}

void npAnimation::ClrMode( mode_t mode ) {
    modeFlags.reset( mode );
}

void npAnimation::StartDelayCounter( uint16_t delay ) {
    ctrDelay.Start( delay );
}

bitset<16> npAnimation::GetModeFlags( void ) {
    return ( modeFlags );
}


int npAnimation::GetID( void ) {
    return ( id );
}

uint32_t npAnimation::GetFrames( void ) {
    return ( frames );
}

uint16_t npAnimation::GetRowBottom() {
    return ( pDisplay->rowBottom );
}

uint16_t npAnimation::GetRowTop() {
    return ( pDisplay->rowTop );
}

uint16_t npAnimation::GetColLeft() {
    return ( pDisplay->colLeft );
}

uint16_t npAnimation::GetColRight() {
    return ( pDisplay->colRight );
}

float npAnimation::Remap( float in, float inMin, float inMax, float outMin, float outMax ) {
        return ( ( in - inMin ) / ( inMax - inMin ) * ( outMax - outMin ) + outMin );
}

void npAnimation::Set( uint16_t x, uint16_t y, rgbw_t color, uint16_t brt ) {
    // calculate scaled brightness relative to global brightness
    uint16_t scaledBrt = (float)brt / 255 * pDisplay->globalBrightness;
    uint16_t index;
    if ( pDisplay != NULL ) {
        if ( ( index = pDisplay->GetColorArrayIndex( x, y ) ) >= 0 ) {  // returns -1 if coords are out of bounds
            pDisplay->frameBuffer[ index ] = ( color.g * ( scaledBrt + 1 ) ) >> 8;
            pDisplay->frameBuffer[ index + 1 ] = ( color.r * ( scaledBrt + 1 ) ) >> 8;
            pDisplay->frameBuffer[ index + 2 ] = ( color.b * ( scaledBrt + 1 ) ) >> 8;
            pDisplay->frameBuffer[ index + 3 ] = ( color.w * ( scaledBrt + 1 ) ) >> 8;
        }
    }
}

// Fill entire display with specified color
void npAnimation::Set( rgbw_t color, uint16_t brt ) {
    uint16_t scaledBrt = (float)brt / 255 * pDisplay->globalBrightness;
    for ( int i = 0; i < pDisplay->GetFrameBytes(); i++ ) {
        pDisplay->frameBuffer[ i ] = ( color.g * ( scaledBrt + 1 ) ) >> 8;
        pDisplay->frameBuffer[ i + 1 ] = ( color.r * ( scaledBrt + 1 ) ) >> 8;
        pDisplay->frameBuffer[ i + 2 ] = ( color.b * ( scaledBrt + 1 ) ) >> 8;
        pDisplay->frameBuffer[ i + 3 ] = ( color.w * ( scaledBrt + 1 ) ) >> 8;        
    }
}

// Clear pixel at specified coordinate
void npAnimation::Clr( uint16_t x, uint16_t y ) {
    uint16_t index;
    if ( pDisplay != NULL ) {
        if ( ( index = pDisplay->GetColorArrayIndex( x, y ) ) >= 0 ) {  // returns -1 if coords are out of bounds
            if ( pDisplay->GetColorMode() == RGB ) {
                pDisplay->frameBuffer[ index ] = 0;
                pDisplay->frameBuffer[ index + 1 ] = 0;
                pDisplay->frameBuffer[ index + 2 ] = 0;
            } 
            else {
                pDisplay->frameBuffer[ index ] = 0;
                pDisplay->frameBuffer[ index + 1 ] = 0;
                pDisplay->frameBuffer[ index + 2 ] = 0;
                pDisplay->frameBuffer[ index + 3 ] = 0;                    
            }
        }
    }
}

// Clear the entire framebuffer if no coords specified
void npAnimation::Clr( void ) {
    pDisplay->ClrFB();
}

// Fills entire row with specified color
void npAnimation::SetRow( uint16_t row, rgbw_t color, uint16_t brt ) {
    for ( int i = 0; i <  pDisplay->numNeopixels; i++ ) {
        Set( i, row, color, brt );
    }
}

void npAnimation::SetRow( uint16_t row, uint16_t xMin, uint16_t xMax, rgbw_t color, uint16_t brt ) {
    if ( xMin < xMax ) {
        for ( int i = xMin; i < xMax; i++ ) {
            Set( i, row, color, brt );
        } 
    } else {
        for ( int i = xMax; i > xMin; i-- ) {
            Set( i, row, color, brt );
        }
    }       
}

void npAnimation::SetRowFade( uint16_t row, float angleStart, float angleStop ) {
    float angleDelta = fabs( angleStop - angleStart ) / pDisplay->numNeopixels;
    for ( int i = 0; i <  pDisplay->numNeopixels; i++ ) {
        Set( i, row, rgbwGetByAngle( angleStart + ( i * angleDelta ), 0 ) );
    }
}

// Fills entire column with specified color
void npAnimation::SetCol( uint16_t col, rgbw_t color, uint16_t brt ) {
    for ( int j = 0; j <= GetRowTop(); j++ ) {
        Set( col, j, color, brt );
    }
}

// Fill column with start/end points specified
void npAnimation::SetCol( uint16_t col, uint16_t yMin, uint16_t yMax, rgbw_t color, uint16_t brt ) {    
    if ( yMin < yMax ) {
        for ( int i = yMin; i <= yMax; i++ ) {
            Set( col, i, color, brt );
        }
    } else {    // if yMin > yMax, we are drawing the column top-to-bottom so reverse the direction of the loop
        for ( int i = yMax; i <= yMin; i++ ) {
            Set( col, i, color, brt );
        }
    }
}

void npAnimation::SetColFade( uint16_t col, float angleStart, float angleStop ) {
    float angleDelta = abs( angleStop - angleStart ) / pDisplay->GetMaxLED();
    for ( int i = 0; i <  pDisplay->GetMaxLED(); i++ ) {
        Set( col, i, rgbwGetByAngle( angleStart + ( i * angleDelta ), 0 ) );
    }
}

void npAnimation::ClrRow( uint16_t row ) {
    for ( int i = 0; i < pDisplay->numNeopixels; i++ ) {
        Clr( i, row );
    }
}

void npAnimation::ClrCol( uint16_t col ) {
    for ( int i = 0; i <  pDisplay->maxLED; i++ ) {
        Clr( col, i );
    }
}

// copy pixel from source to destination
void npAnimation::Cpy( uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2 ) {
    rgbw_t color = pDisplay->GetColorAtCoord( x1, y1 );
    Set( x2, y2, color );
}

// Mov pixel from source to destination
void npAnimation::Mov( uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2 ) {
    // rgbw_t color = pDisplay->GetColorAtCoord( x1, y1 );
    // Set( x2, y2, color );
    // Clr( x1, y1 );
    if ( pDisplay != NULL ) {
        uint16_t index1 = pDisplay->GetColorArrayIndex( x1, y1 );
        uint16_t index2 = pDisplay->GetColorArrayIndex( x2, y2 );
        if ( ( index1 && index2 ) ) {  // valid coordinates in buffer
            pDisplay->frameBuffer[ index2 ] = pDisplay->frameBuffer[ index1 ];
            pDisplay->frameBuffer[ index2 + 1 ] = pDisplay->frameBuffer[ index1 + 1 ];
            pDisplay->frameBuffer[ index2 + 2 ] = pDisplay->frameBuffer[ index1 + 2 ];
            pDisplay->frameBuffer[ index2 + 2 ] = pDisplay->frameBuffer[ index1 + 3 ];
            Clr( x1, y1 );
        }
    }    
}

// Swap pixels
void npAnimation::Swap( uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2 ) {
    rgbw_t color1 = pDisplay->GetColorAtCoord( x1, y1 );
    rgbw_t color2 = pDisplay->GetColorAtCoord( x2, y2 );
    Set( x2, y2, color1 );
    Set( x1, y1, color2 );
}

void npAnimation::CpyRow( uint16_t src, uint16_t dest ) {
    for ( int i = 0; i <  pDisplay->numNeopixels; i++ ) {
        rgbw_t clr = pDisplay->GetColorAtCoord( i, src );
        Set( i, dest, clr );
    }
}

void npAnimation::ShiftLeft() {
    for ( int i = pDisplay->colLeft; i < pDisplay->colRight; i++ ) {
        for ( int j = pDisplay->rowBottom; j <= pDisplay->rowTop; j++ ) {
            int idx1 = pDisplay->GetColorArrayIndex( i, j );    // LED on this column
            int idx2 = pDisplay->GetColorArrayIndex( i + 1, j );  // LED on the next column
            if ( idx1 >= 0 && idx2 >= 0 ) {
                pDisplay->frameBuffer[ idx1 ] = pDisplay->frameBuffer[ idx2 ]; 
                pDisplay->frameBuffer[ idx1+1 ] = pDisplay->frameBuffer[ idx2+1 ];
                pDisplay->frameBuffer[ idx1+2 ] = pDisplay->frameBuffer[ idx2+2 ];
                pDisplay->frameBuffer[ idx1+3 ] = pDisplay->frameBuffer[ idx2+3 ];
            }
        }        
    }
    ClrCol( pDisplay->colRight );
}

void npAnimation::ShiftLeft( uint16_t colLeft, uint16_t colRight ) {
    for ( int i = colLeft; i < colRight; i++ ) {
        for ( int j = pDisplay->rowBottom; j <= pDisplay->rowTop; j++ ) {
            int idx1 = pDisplay->GetColorArrayIndex( i, j );    // LED on this column
            int idx2 = pDisplay->GetColorArrayIndex( i + 1, j );  // LED on the next column
            if ( idx1 >= 0 && idx2 >= 0 ) {
                pDisplay->frameBuffer[ idx1 ] = pDisplay->frameBuffer[ idx2 ]; 
                pDisplay->frameBuffer[ idx1+1 ] = pDisplay->frameBuffer[ idx2+1 ];
                pDisplay->frameBuffer[ idx1+2 ] = pDisplay->frameBuffer[ idx2+2 ];
                pDisplay->frameBuffer[ idx1+3 ] = pDisplay->frameBuffer[ idx2+3 ];
            }
        }        
    }    
    ClrCol( colRight );
}

void npAnimation::ShiftRight() {
    for ( int i = pDisplay->colRight; i > pDisplay->colLeft; i-- ) {
        for ( int j = pDisplay->rowBottom; j <= pDisplay->rowTop; j++ ) {
            int idx1 = pDisplay->GetColorArrayIndex( i, j );    // LED on this column
            int idx2 = pDisplay->GetColorArrayIndex( i - 1, j );  // LED on the previous column
            if ( idx1 >= 0 && idx2 >= 0 ) {
                pDisplay->frameBuffer[ idx1 ] = pDisplay->frameBuffer[ idx2 ]; 
                pDisplay->frameBuffer[ idx1+1 ] = pDisplay->frameBuffer[ idx2+1 ];
                pDisplay->frameBuffer[ idx1+2 ] = pDisplay->frameBuffer[ idx2+2 ];
                pDisplay->frameBuffer[ idx1+3 ] = pDisplay->frameBuffer[ idx2+3 ];
            }
        }        
    }    
    ClrCol( pDisplay->colLeft );
}

void npAnimation::ShiftRight( uint16_t colLeft, uint16_t colRight ) {
    for ( int i = colRight; i > colLeft; i-- ) {
        for ( int j = pDisplay->rowBottom; j <= pDisplay->rowTop; j++ ) {
            int idx1 = pDisplay->GetColorArrayIndex( i, j );    // LED on this column
            int idx2 = pDisplay->GetColorArrayIndex( i - 1, j );  // LED on the previous column
            if ( idx1 >= 0 && idx2 >= 0 ) {
                pDisplay->frameBuffer[ idx1 ] = pDisplay->frameBuffer[ idx2 ]; 
                pDisplay->frameBuffer[ idx1+1 ] = pDisplay->frameBuffer[ idx2+1 ];
                pDisplay->frameBuffer[ idx1+2 ] = pDisplay->frameBuffer[ idx2+2 ];
                pDisplay->frameBuffer[ idx1+3 ] = pDisplay->frameBuffer[ idx2+3 ];
            }
        }        
    }    
    ClrCol( colLeft );
}

void npAnimation::ShiftUp() {
    for ( int i = pDisplay->colLeft; i <= pDisplay->colRight; i++ ) {
        for ( int j = pDisplay->rowTop; j > pDisplay->rowBottom; j-- ) {
            int idx1 = pDisplay->GetColorArrayIndex( i, j );    // LED on this row
            int idx2 = pDisplay->GetColorArrayIndex( i, j-1 );  // LED on row below
            if ( idx1 >= 0 && idx2 >= 0 ) {
                pDisplay->frameBuffer[ idx1 ] = pDisplay->frameBuffer[ idx2 ]; 
                pDisplay->frameBuffer[ idx1+1 ] = pDisplay->frameBuffer[ idx2+1 ];
                pDisplay->frameBuffer[ idx1+2 ] = pDisplay->frameBuffer[ idx2+2 ];
                pDisplay->frameBuffer[ idx1+3 ] = pDisplay->frameBuffer[ idx2+3 ];
            }
        }        
    }    
    ClrRow( pDisplay->rowBottom );
}

void npAnimation::ShiftColUp( uint16_t col ) {    
    for ( int j = pDisplay->rowTop; j > pDisplay->rowBottom; j-- ) {
        int idx1 = pDisplay->GetColorArrayIndex( col, j );    // LED on this row
        int idx2 = pDisplay->GetColorArrayIndex( col, j-1 );  // LED on row below
        if ( idx1 >= 0 && idx2 >= 0 ) {
            pDisplay->frameBuffer[ idx1 ] = pDisplay->frameBuffer[ idx2 ]; 
            pDisplay->frameBuffer[ idx1+1 ] = pDisplay->frameBuffer[ idx2+1 ];
            pDisplay->frameBuffer[ idx1+2 ] = pDisplay->frameBuffer[ idx2+2 ];
            pDisplay->frameBuffer[ idx1+3 ] = pDisplay->frameBuffer[ idx2+3 ];
        }
    }        
    
    Clr( col, 0 );
}

void npAnimation::ShiftUp( uint16_t rowBottom, uint16_t rowTop ) {
    for ( int i = pDisplay->colLeft; i <= pDisplay->colRight; i++ ) {
        for ( int j = rowTop; j > rowBottom; j-- ) {
            int idx1 = pDisplay->GetColorArrayIndex( i, j );    // LED on this row
            int idx2 = pDisplay->GetColorArrayIndex( i, j - 1 );  // LED on row below
            if ( idx1 >= 0 && idx2 >= 0 ) {
                pDisplay->frameBuffer[ idx1 ] = pDisplay->frameBuffer[ idx2 ]; 
                pDisplay->frameBuffer[ idx1+1 ] = pDisplay->frameBuffer[ idx2+1 ];
                pDisplay->frameBuffer[ idx1+2 ] = pDisplay->frameBuffer[ idx2+2 ];
                pDisplay->frameBuffer[ idx1+3 ] = pDisplay->frameBuffer[ idx2+3 ];
            }
        }        
    }    
    ClrRow( rowBottom );
}

void npAnimation::ShiftDown() {    
    for ( int i = pDisplay->colLeft; i <= pDisplay->colRight; i++ ) {
        for ( int j = pDisplay->rowBottom; j < pDisplay->rowTop; j++ ) {
            int idx1 = pDisplay->GetColorArrayIndex( i, j );    // LED on this row
            int idx2 = pDisplay->GetColorArrayIndex( i, j + 1 );  // LED on row above
            if ( idx1 >= 0 && idx2 >= 0 ) {              
                pDisplay->frameBuffer[ idx1 ] = pDisplay->frameBuffer[ idx2 ]; 
                pDisplay->frameBuffer[ idx1+1 ] = pDisplay->frameBuffer[ idx2+1 ];
                pDisplay->frameBuffer[ idx1+2 ] = pDisplay->frameBuffer[ idx2+2 ];
                pDisplay->frameBuffer[ idx1+3 ] = pDisplay->frameBuffer[ idx2+3 ];
                
            }
        }        
    }    
    ClrRow( pDisplay->rowTop );
}

void npAnimation::ShiftDown( uint16_t rowBottom, uint16_t rowTop ) {    
    for ( int i = pDisplay->colLeft; i <= pDisplay->colRight; i++ ) {
        for ( int j = rowBottom; j < rowTop; j++ ) {
            int idx1 = pDisplay->GetColorArrayIndex( i, j );    // LED on this row
            int idx2 = pDisplay->GetColorArrayIndex( i, j + 1 );  // LED on row above
            if ( idx1 >= 0 && idx2 >= 0 ) {                
                pDisplay->frameBuffer[ idx1 ] = pDisplay->frameBuffer[ idx2 ]; 
                pDisplay->frameBuffer[ idx1+1 ] = pDisplay->frameBuffer[ idx2+1 ];
                pDisplay->frameBuffer[ idx1+2 ] = pDisplay->frameBuffer[ idx2+2 ];
                pDisplay->frameBuffer[ idx1+3 ] = pDisplay->frameBuffer[ idx2+3 ];
                
            }
        }        
    }    
    ClrRow( rowTop );
}

void npAnimation::FadeOut( int fadeMode, int numSteps, uint16_t minBrt ) {
    int brtStep, tmp;       // tmp needs to be int so we can detect underflow in if-test when using step method
    if ( fadeMode == 1 ) {  // NOTE: MODE 1 IS NOT CURRENTLY WORKING
        brtStep = 255 / numSteps;
    }
        
    for ( int i = 0; i < pDisplay->GetFrameBytes(); i++ ) {
        if ( fadeMode == 1 ) {  // use step method
            tmp = pDisplay->frameBuffer[ i ];
            if ( ( tmp -= brtStep ) <= 0 ) {
                pDisplay->frameBuffer[ i ] = 0;
            } else {
                pDisplay->frameBuffer[ i ] -= tmp;
            }                
        } else {    // use shift method
            // if ( pDisplay->frameBuffer[ i ] ) {         // if current color is non-zero
            //    if ( ( pDisplay->frameBuffer[ i ] >> 1 ) >= minBrt ) {  // shift as long as we wont't undershoot minimum brightness 
                    pDisplay->frameBuffer[ i ] >>= 1;
            //    }                
            // }   
        }
    }    
}

int npAnimation::PollGlobalModes() {
    switch ( globalMode.msg ) {
        case LCD_DISPLAY_ON: // maintained
            modeFlags.reset( MODE_OFF );
            break;
            
        case LCD_DISPLAY_OFF: // maintained
            modeFlags.set( MODE_OFF );
            ret = MODE_OFF;
            break;
            
        case LCD_MODE_PAUSE_ON: // maintained
            modeFlags.set( MODE_PAUSE );
            ret = MODE_PAUSE;
            break;
            
        case LCD_MODE_PAUSE_OFF: // maintained
            modeFlags.reset ( MODE_PAUSE );
            break;
            
        case LCD_MODE_REPEAT_ON: // maintained
            modeFlags.set( MODE_REPEAT );
            break;
            
        case LCD_MODE_REPEAT_OFF: // maintained
            modeFlags.reset ( MODE_REPEAT );
            break;
            
        case LCD_MODE_STBY_ON:  // maintained

            break;
            
        case LCD_MODE_STBY_OFF: // maintained

            break;
            
        case LCD_MODE_PREVIOUS:
            ret = MODE_PREV;
            skip = 1;
            break;
            
        case LCD_MODE_NEXT:
            ret = MODE_NEXT;
            skip = 1;
            break;
            
        case LCD_BRIGHT_0:
            pDisplay->SetBrightness( 200 * 0.1);
            break;
            
        case LCD_BRIGHT_1:
            pDisplay->SetBrightness( 200 * 0.2);    
            break;

        case LCD_BRIGHT_2:
            pDisplay->SetBrightness( 200 * 0.3);
            break;

        case LCD_BRIGHT_3:
            pDisplay->SetBrightness( 200 * 0.4);     
            break;

        case LCD_BRIGHT_4:
            pDisplay->SetBrightness( 200 * 0.5);    
            break;

        case LCD_BRIGHT_5:
            pDisplay->SetBrightness( 200 * 0.6);    
            break;

        case LCD_BRIGHT_6:
            pDisplay->SetBrightness( 200 * 0.7);    
            break;

        case LCD_BRIGHT_7:
            pDisplay->SetBrightness( 200 * 0.8);    
            break;

        case LCD_BRIGHT_8:
            pDisplay->SetBrightness( 200 * 0.9);    
            break;

        case LCD_BRIGHT_9:
            pDisplay->SetBrightness( 200 );    
            break;
            
        case LCD_FADE_0:

            break;
            
        case LCD_FADE_1:

            break;

        case LCD_FADE_2:

            break;

        case LCD_FADE_3:
  
            break;

        case LCD_FADE_4:

            break;

        case LCD_FADE_5:

            break;

        case LCD_FADE_6:

            break;

        case LCD_FADE_7:

            break;

        case LCD_FADE_8:

            break;

        case LCD_FADE_9:

            break;
            
        case LCD_STROBE_0:
            strobeRate = ( 80 * 0.1 );    
            break;
            
        case LCD_STROBE_1:
            strobeRate = ( 80 * 0.2 );
            break;

        case LCD_STROBE_2:
            strobeRate = ( 80 * 0.3 );
            break;

        case LCD_STROBE_3:
            strobeRate = ( 80 * 0.4 );
            break;

        case LCD_STROBE_4:
            strobeRate = ( 80 * 0.5 );
            break;

        case LCD_STROBE_5:
            strobeRate = ( 80 * 0.6 );
            break;

        case LCD_STROBE_6:
            strobeRate = ( 80 * 0.7 );
            break;

        case LCD_STROBE_7:
            strobeRate = ( 80 * 0.8 );
            break;

        case LCD_STROBE_8:  
            strobeRate = ( 80 * 0.9 );
            break;

        case LCD_STROBE_9:
            strobeRate = ( 80 );
            break;                       
            
        // lower slider, higher number
        case LCD_GAIN_0:
            dbGain = ( 35 * 0.55 );    
            break;
            
        case LCD_GAIN_1:
            dbGain = ( 35 * 0.6 );
            break;

        case LCD_GAIN_2:
            dbGain = ( 35 * 0.65 );
            break;

        case LCD_GAIN_3:
            dbGain = ( 35 * 0.7 );
            break;

        case LCD_GAIN_4:
            dbGain = ( 35 * 0.75 );
            break;

        case LCD_GAIN_5:
            dbGain = ( 35 * 0.8 );
            break;

        case LCD_GAIN_6:
            dbGain = ( 35 * 0.85 );
            break;

        case LCD_GAIN_7:
            dbGain = ( 35 * 0.9 );
            break;

        case LCD_GAIN_8:  
            dbGain = ( 35 * 0.95 );
            break;

        case LCD_GAIN_9:
            dbGain = ( 35 );
            break;
            
        default:
            break;
    }
    
    if ( modeFlags.test( MODE_OFF ) || modeFlags.test( MODE_PAUSE ) ) {
        skip = 1;
    } else {
        skip = 0;
    }
    
    globalMode.msg = 0;
    globalMode.msgPending = 0;
    
    return 0;
}

void npAnimation::RefreshDisplay() {
    pDisplay->Refresh();
}
