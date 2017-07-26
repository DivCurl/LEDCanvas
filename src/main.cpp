#include "./include/main.h"

#define DEBUG_LEVEL 0

// PIC32 chip-specific configuration bits
#pragma config FSRSSEL      = PRIORITY_7    // Assign shadow register set to IPL7 interrupts
#pragma config POSCMOD      = HS            // Enable high speed oscillator module
#pragma config FNOSC        = PRIPLL        // use primary PLL
#pragma config FPLLIDIV     = DIV_2         // Divide 8MHz crystal clock by 2 for 4MHz to PLL input
#pragma config FPLLMUL      = MUL_20        // Multiply PLL by 20 (=80MHz)
#pragma config FPLLODIV     = DIV_1         // PLL output divide by 1 (=80MHZ Fcy)
#pragma config FPBDIV       = DIV_1         // Divide core clock by 1 for peripheral bus (=80MHz Fpb)
#pragma config FSOSCEN      = OFF           // Disable secondary oscillator
#pragma config FWDTEN       = OFF           // Disable Watchdog timer
#pragma config CP           = OFF           // Disable code protect
#pragma config BWP          = OFF           // Disable boot write protect
#pragma config PWP          = OFF           // Disable program write protect

using namespace std;

int T4Period = PB_FREQ / ADC_SAMPLE_FREQ;           // 20 Khz period; 10 Khz effective for audio FFT
volatile uint32_t t2Ticks = 0;
volatile uint32_t ticks = 0;
uint16_t _1_ms_tick;
extern int16c sampleBuffer[];  
extern bool analyzerRun;
extern volatile bool FFTBufferReady;
extern int sampleIndex;
extern int uartBytesRead;
extern uint64_t lcdReadBuffer;
   
int main() {          
    SYSTEMConfigPerformance( SYS_FREQ );
    mJTAGPortEnable( DEBUG_JTAGPORT_OFF );
    INTEnableSystemMultiVectoredInt();
    InitADC();
    InitUART();             
    _1_ms_tick = ( uint16_t )round( ( SYS_FREQ / T4Period ) * 0.001f - 1 ) ;
    CloseTimer4();
    OpenTimer4( T4_ON | T4_SOURCE_INT | T4_PS_1_1, T4Period );  
    ConfigIntTimer4( T4_INT_ON | T4_INT_PRIOR_7 ); 
    
    // Startup delay to give LCD time to boot
#if DEBUG_LEVEL == 0
    counter startup( 2000 );
    startup.Start();
    while ( !startup.Update() );    
    InitLCD();
#endif
    
    int currAnim = 1;
    npAnimation* pAnim;
    npDisplay display( RGBW );   
    display.SetBrightness( 200 );
    display.AddNeopixel( 60, &LATBSET, &LATBCLR, &TRISB, portPin[ 0 ] );
    display.AddNeopixel( 60, &LATBSET, &LATBCLR, &TRISB, portPin[ 1 ] );
    display.AddNeopixel( 60, &LATBSET, &LATBCLR, &TRISB, portPin[ 2 ] );
    display.AddNeopixel( 60, &LATBSET, &LATBCLR, &TRISB, portPin[ 3 ] );
    display.AddNeopixel( 60, &LATBSET, &LATBCLR, &TRISB, portPin[ 4 ] );
    display.AddNeopixel( 60, &LATBSET, &LATBCLR, &TRISB, portPin[ 5 ] );   
    // RB6 and RB7 used for ICSP on my board so I'm not using these pins here. 
    // It doesn't hurt anything to have these connected, just prevents 
    // junk from being clocked out to those LED strips while flashing the PIC. 
    display.AddNeopixel( 60, &LATBSET, &LATBCLR, &TRISB, portPin[ 8 ] );
    display.AddNeopixel( 60, &LATBSET, &LATBCLR, &TRISB, portPin[ 9 ] );
    display.AddNeopixel( 60, &LATBSET, &LATBCLR, &TRISB, portPin[ 10 ] );
    // Add more as desired...
    srand( ReadADC10( 0 ) ); 
           
    /* TODO:
     * 
     *  1. Add some randomization to animation options (number of frames, color modes, fading, etc)    
     *  2. This implementation will not save specific settings from the touch screen. Is this needed?
     *  3. 
     *  4. 
     */
    
    while ( 1 ) {
        if ( ( currAnim == ID_AN_NONE ) || ( currAnim >= ID_AN_MAX ) ) {
            currAnim = 1;
        }
                
        switch ( currAnim ) {  
            
            case ( ID_AN_TEST ):
                pAnim = new anTest( &display, MODE_REPEAT, 3000 );
                
                if ( pAnim->Draw() == MODE_PREV ) {
                    currAnim--;
                } else {
                    currAnim++;
                }
                
                delete pAnim;
                break;
            
            case ( ID_AN_CHEVRONS ):
                pAnim = new anChevrons( &display, MODE_NONE, 1500 );
                
                if ( pAnim->Draw() == MODE_PREV ) {
                    currAnim--;
                } else {
                    currAnim++;
                }
                
                delete pAnim;
                break;
            
            case ( ID_AN_COMETS ):
                pAnim = new anComets( &display, MODE_NONE, 1500 );
                
                if ( pAnim->Draw() == MODE_PREV ) {
                    currAnim--;
                } else {
                    currAnim++;
                }
                
                delete pAnim;
                break;
                
            case ( ID_AN_FADEMIDDLE ):
                pAnim = new anFadeMiddle( &display, MODE_NONE, 1500 );
                
                if ( pAnim->Draw() == MODE_PREV ) {
                    currAnim--;
                } else {
                    currAnim++;
                }
                
                delete pAnim;
                break;
                
            case ( ID_AN_RAIN ):
                pAnim = new anRain( &display, MODE_NONE, 1500 );
                
                if ( pAnim->Draw() == MODE_PREV ) {
                    currAnim--;
                } else {
                    currAnim++;
                }
                
                delete pAnim;
                break;
                
            case ( ID_AN_RAINBOWCHASER ):
                pAnim = new anRainbowChaser( &display, MODE_NONE, 1000 );
                
                if ( pAnim->Draw() == MODE_PREV ) {
                    currAnim--;
                } else {
                    currAnim++;
                }
                
                delete pAnim;
                break;
                                                   
            case ( ID_AN_CLASSIC_SA ):
                pAnim = new anClassicSA( &display, MODE_REPEAT, 3000 );
                
                if ( pAnim->Draw() == MODE_PREV ) {
                    currAnim--;
                } else {
                    currAnim++;
                
                }
                
                delete pAnim;
                break;
                
            case ( ID_AN_COLORFLOW_SA ):
                pAnim = new anColorFlowSA( &display, MODE_NONE, 3000 );
                
                if ( pAnim->Draw() == MODE_PREV ) {
                    currAnim--;
                } else {
                    currAnim++;
                }
                
                delete pAnim;
                break;
                
            case ( ID_AN_COLORRACE_SA ):
                pAnim = new anColorRaceSA( &display, MODE_NONE, 3000 );
                
                if ( pAnim->Draw() == MODE_PREV ) {
                    currAnim--;
                } else {
                    currAnim++;
                }
                
                delete pAnim;
                break;
                
            case ( ID_AN_PULSEFADE_SA ):
               pAnim = new anPulseFadeSA( &display, MODE_NONE, 3000 );
               
                if ( pAnim->Draw() == MODE_PREV ) {
                    currAnim--;
                } else {
                    currAnim++;
                }
               
                delete pAnim;
                break;
                
            case ( ID_AN_SPLATTER_SA ):
                pAnim = new anSplatterSA( &display, MODE_REPEAT, 3000 );
                
                if ( pAnim->Draw() == MODE_PREV ) {
                    currAnim--;
                } else {
                    currAnim++;
                }
                
                delete pAnim;
                break;                
            
            case ( ID_AN_TETRIS_SA ):
                pAnim = new anTetrisSA( &display, MODE_REPEAT, 3000 );
                
                if ( pAnim->Draw() == MODE_PREV ) {
                    currAnim--;
                } else {
                    currAnim++;
                }
                
                delete pAnim;                
                break;             
            
            default : 
                currAnim++;
                delete pAnim;
                break;                        
        }
    }
    
    return ( EXIT_SUCCESS );
}

// Note - electret mic wired to AI15
void InitADC( void ) {   
    CloseADC10();
    SetChanADC10( ADC_CH0_NEG_SAMPLEA_NVREF );
    OpenADC10( ADC_CONFIG1, ADC_CONFIG2, ADC_CONFIG3, ADC_CONFIGPORT, ADC_CONFIGSCAN );
    EnableADC10(); 
    while ( !mAD1GetIntFlag() ) {}
}

// Note - tx/rx pins J14-1 & J14-3 on Max32 board
void InitUART( void ) {
    int PB_CLOCK = 80000000;
    int BAUD = 9600;
    OpenUART1( UARTCONFIG1, UARTCONFIG2, PB_CLOCK/16/BAUD - 1 );
    ConfigIntUART1( UART_INT_PR1 | UART_RX_INT_EN );    
}

void InitLCD( void ) {
    LCDSendMessage( LCD_SET_DISPLAY_ON, 6 ); 
    LCDSendMessage( LCD_SET_BRIGHT_5, 6 ); 
    LCDSendMessage( LCD_SET_FADE_4, 6 ); 
    LCDSendMessage( LCD_SET_STROBE_4, 6 ); 
    LCDSendMessage( LCD_SET_GAIN_4, 6 ); 
}

// Timer4 interrupt for accurate timing
extern "C"
void __ISR ( _TIMER_4_VECTOR, IPL7AUTO ) TMR4IntHandler( void ) {    
    mT4ClearIntFlag(); 
    
    if ( ticks++ == _1_ms_tick ) {
        t2Ticks++;  
        ticks = 0;
    } 
    
    if ( analyzerRun ) {               
        int16_t s = ReadADC10( 0 );
        // some very basic noise rejection before storing sample   
        sampleBuffer[ sampleIndex ].re = ( s > ( ADC_COUNT_BIAS - ADC_COUNT_NOISE ) ) && ( s < ( ADC_COUNT_BIAS + ADC_COUNT_NOISE ) ) ? 0 : s - ADC_COUNT_ZERO ;
        sampleBuffer[ sampleIndex ].im = 0;
        
        if ( sampleIndex == ( N - 1 ) ) {
            sampleIndex = 0;
            FFTBufferReady = 1;
        } else {
            sampleIndex++;
        }        
    }
    
    // mT4ClearIntFlag(); 
} 

// UART1 interrupt for serial communications
extern "C"
void __ISR( _UART1_VECTOR, IPL1AUTO ) UART1IntHandler( void ) {
    if ( mU1RXGetIntFlag() ) {        
        LCDReadByte();        
        
        if ( uartBytesRead == 6 ) {
            globalMode.msgPending = 1;
            globalMode.msg = lcdReadBuffer;
            lcdReadBuffer = 0;
        }
        
        mU1RXClearIntFlag();          
    }
    // Don't care about tx interrupts, return immediately
    if ( mU1TXGetIntFlag() ) {
        mU1TXClearIntFlag();
    }
}
