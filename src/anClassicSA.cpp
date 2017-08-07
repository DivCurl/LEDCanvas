#include "./include/anClassicSA.h"

// Refer to fft.h/fft.cpp
extern bool analyzerRun;
extern volatile bool FFTBufferReady;
extern short singleSidedFFT[ N ];

anClassicSA::anClassicSA( npDisplay* pDisplay, mode_t mode, int frames, opt_t opts, scale_t customScaling )
 : npAnimation( pDisplay, mode, frames, opts, customScaling ) {
    // Sync current animation runtime mode settings to LCD display
    if ( modeFlags.test( MODE_REPEAT ) ) {
        LCDSendMessage( LCD_SET_REPEAT_ON, 6 );
    } else {
        LCDSendMessage( LCD_SET_REPEAT_OFF, 6 );
    }

    analyzerRun = 1;    // used by T4 ISR
    InitFFT();
}

anClassicSA::~anClassicSA() {
    analyzerRun = 0;
}

int anClassicSA::Draw() {
    int binCount = GetColCount() * 2; // alternating upper/lower half of display
    float colorAngle = rand() % 360;
    float fadeDelta = 5.0;
    int whiteTemp = rand() % 20;

    // int binDelta = round( (float)( N / 2 ) / binCount  ) - 1;
    vector<pixel> freqBars[ binCount ]; // array of pixel vectors for each frequency bar to be drawn
    pixel peaks[ binCount ]; // the peak pixel position for each frequency bar
    counter ctrMain, ctrFade, ctrPeakFallDelay[ binCount ];
    ctrFade.Start( 500 );
    ctrMain.Start( 25 );

    for ( int i = 0; i < binCount; i ++ ) {
        freqBars[ i ].reserve( GetColCount() );
        // set initial peak y-coords to upper/lower row origin
        if ( i % 2 != 0 ) { // odd
            peaks[ i ].coord.y = 30;
        }
        else { // even
            peaks[ i ].coord.y = 29;
        }
    }
    // Main animation loop
    while ( ( framesDrawn < frames ) || modeFlags.test( MODE_REPEAT ) ) {
        if ( globalMode.msgPending ) {
            PollGlobalModes();  // handle any new external I/O messages
        }

        if ( modeFlags.test( MODE_OFF ) ) {
            Clr();
        }

        if ( ret == MODE_PREV || ret == MODE_NEXT ) {
            return ( ret );  // break while loop and return to main signaling next/prev animation to be drawn
        }

        if ( !skip ) {
            if ( FFTBufferReady ) {
                ComputeFFT();
            }

            if ( ctrFade.Done() ) {
                ctrFade.Reset();
                if ( ++colorAngle > 360.0f ) {
                    colorAngle -= 360.0f;
                }
            }

            if ( ctrMain.Done() ) {
                ctrMain.Reset();

                for ( int bin = 0; bin < binCount; bin++ ) {
                    int barLength = Remap ( singleSidedFFT[ bin ], -54, -20, 0, 29 );

                    if ( !barLength || ( barLength < freqBars[ bin ].size() ) ) { // new bar is shorter
                        freqBars[ bin ].pop_back(); // drop bar by one pixel

                        if ( ctrPeakFallDelay[ bin ].Done() ) { // allow peak pixel to start falling
                            if ( bin % 2 != 0 ) { // odd bin; peaks fall downwards
                                if ( ( peaks[ bin].coord.y - 1 ) < 30 ) {
                                    peaks[ bin].color = rgbw_t { 0, 0, 0, 0 };
                                }
                                else {
                                    peaks[ bin].coord.y -= 1;
                                }
                            }
                            else { // even bin; peaks 'fall' upwards
                                if ( ( peaks[ bin].coord.y + 1 ) > 29 ) {
                                    peaks[ bin].color = rgbw_t { 0, 0, 0, 0 };
                                }
                                else {
                                    peaks[ bin].coord.y += 1;
                                }
                            }
                        }
                    }
                    else { // new bar is longer; regenerate bar
                        freqBars[ bin ].clear();

                        if ( bin % 2 != 0 ) { // odd bin; draw towards top
                            for ( int j = 0; j <= barLength; j++ ) {
                                freqBars[ bin ].push_back(
                                    pixel( coord2d_t { bin / 2, 30 + j },
                                    rgbwGetByAngle ( colorAngle + ( j * fadeDelta ), whiteTemp  ),
                                    255 )
                                );
                            }

                            if ( ( 30 + barLength ) > peaks[ bin].coord.y ) { // draw new peak pixel (upper half) when bar size is larger than last
                                peaks[ bin ].coord.x = bin / 2 ;
                                peaks[ bin ].coord.y = 30 + barLength;
                                peaks[ bin ].color = rgbwGetByAngle ( colorAngle + 180 );
                                ctrPeakFallDelay[ bin ].Reset( 500 );
                            }
                        }
                        else { // even bin; draw towards bottom
                            for ( int j = 0; j <= barLength; j++ ) {
                                freqBars[ bin ].push_back(
                                    pixel( coord2d_t { bin / 2, 29 - j },
                                    rgbwGetByAngle ( colorAngle + ( j * fadeDelta ), whiteTemp ),
                                    255 )
                                );
                            }

                            if ( ( 29 - barLength ) < peaks[ bin].coord.y ) { // draw new peak pixel (lower half) when bar size is larger than last
                                peaks[ bin ].coord.x = bin / 2;
                                peaks[ bin ].coord.y = 29 - barLength;
                                peaks[ bin ].color = rgbwGetByAngle ( colorAngle + 180 );
                                ctrPeakFallDelay[ bin ].Reset( 500 );
                            }
                        }
                    }

                    Set( peaks[ bin ] );
                    Blit( freqBars[ bin ] );

                }

                RefreshDisplay( FB_CLEAR );
                framesDrawn++;
            }
        }
    } // end main loop   

    return ( MODE_NEXT );
}
