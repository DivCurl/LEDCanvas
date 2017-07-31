#include "./include/anColorRaceSA.h" 

// Refer to fft.h/fft.cpp
extern bool analyzerRun;
extern volatile bool FFTBufferReady;
extern short singleSidedFFT[ N ];

anColorRaceSA::anColorRaceSA( npDisplay* pDisplay, mode_t mode, int frames, opt_t opts, scale_t customScaling ) 
 : npAnimation( pDisplay, mode, frames, opts, customScaling ) {
    // Sync current animation runtime mode settings to LCD display
    if ( modeFlags.test( MODE_REPEAT ) ) {
        LCDSendMessage( LCD_SET_REPEAT_ON, 6 );   
    }
    else {
        LCDSendMessage( LCD_SET_REPEAT_OFF, 6 );   
    }
    
    analyzerRun = 1;    // used by T4 ISR
    InitFFT();
}

anColorRaceSA::~anColorRaceSA() {
    analyzerRun = 0;
}

int anColorRaceSA::Draw() {    
    StartDelayCounter( 25 ); 
    
    // Main animation loop
    while ( ( framesDrawn < frames ) || modeFlags.test( MODE_REPEAT ) ) {
        if ( globalMode.msgPending ) { 
            PollGlobalModes();  // handle any new external I/O messages
        }
                
        if ( modeFlags.test( MODE_OFF ) ) {
            Clr();
        }
            
        if ( ret == MODE_PREV || ret == MODE_NEXT ) {
            break;  // break while loop and return to main signaling next/prev animation to be drawn
        }
    
        if ( !skip ) { 
            int barLength;
            static int remainingShifts[ 9 ];
            
            if ( FFTBufferReady ) {
                ComputeFFT();
            }            
            
            // Each update, check remaining column shifts. While there are some left, shift the column up.
            if ( ctrDelay.Done() ) {
                ctrDelay.Reset();
                
                for ( int i = 0; i < 9; i++ ) {
                    if ( remainingShifts[ i ] > 0 ) {
                        ShiftColUp( i );
                        remainingShifts[ i ]--;
                    }
                }
            }

            for ( int i = 0; i <= GetColRight(); i++ ) {   // loop across x (frequency) axis, lower & upper halves    
                // Update height
                for ( int j = 0; j <= 59; j++ ) {           
                    if ( Remap ( singleSidedFFT[ i + 3 ], -50, -dbGain, 0, 15 ) > j ) {   
                        barLength = j;
                    }            
                }           

                if ( barLength > 0 /* && !remainingShifts [ i ] */ ) {        
                    SetCol( i, GetRowBottom(), barLength, rgbwGetByAngle( angle + (i * 30 ), rand() % 16  ) ); 
                    remainingShifts[ i ] = barLength;
                }
                
                barLength = 0;
            }

            if ( ( angle += 3 ) > 360 ) { 
                angle -= 360 ;
            }
            
            framesDrawn++;
        }      
            
        RefreshDisplay();
    } // main end loop
    
    return ( ret );
}
