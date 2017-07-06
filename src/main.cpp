#include "./include/main.h"

#define _DEBUG 0

// Chip configuration
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

int currAnim;
int T4Period = 3000;           // 40 Khz period; 20 Khz effective for audio FFT
volatile uint32_t t2Ticks = 0;
volatile uint32_t ticks = 0;
int _1_ms_tick;
extern int16c sampleBuffer[];   // initialize buffer to collect samples
extern int analyzerRun;
extern int sampleIndex;
extern int uartBytesRead;
extern bool isReadPacket;
extern uint64_t lcdReadBuffer;
   
int main() {   
    SYSTEMConfigPerformance( SYS_FREQ );
    mJTAGPortEnable( DEBUG_JTAGPORT_OFF );
    INTEnableSystemMultiVectoredInt();   
    InitADC();
    InitUART();    
    CloseTimer4();
    OpenTimer4( T4_ON | T4_SOURCE_INT | T4_PS_1_1, T4Period );  
    ConfigIntTimer4( T4_INT_ON | T4_INT_PRIOR_7 );    
    srand( ReadADC10( 0 ) );   
    _1_ms_tick = (float) ( SYS_FREQ / T4Period ) * 0.001;
    
    // give LCD time to boot
#if _DEBUG == 0
    counter startup( 2000 );
    startup.Start();
    while ( !startup.Update() );    
    InitLCD();
#endif
    
    npDisplay display( RGBW );   
    display.SetBrightness( 120 );
    display.AddNeopixel( 60, &LATBSET, &LATBCLR, &TRISB, portPin[ 0 ] );
    display.AddNeopixel( 60, &LATBSET, &LATBCLR, &TRISB, portPin[ 1 ] );
    display.AddNeopixel( 60, &LATBSET, &LATBCLR, &TRISB, portPin[ 2 ] );
    display.AddNeopixel( 60, &LATBSET, &LATBCLR, &TRISB, portPin[ 3 ] );
    display.AddNeopixel( 60, &LATBSET, &LATBCLR, &TRISB, portPin[ 4 ] );
    display.AddNeopixel( 60, &LATBSET, &LATBCLR, &TRISB, portPin[ 5 ] );   
    // RB6 and RB7 used for ICSP so skip these pins. Doesn't hurt anything to have them wired there, 
    // just prevents junk from being clocked to those LED strips when downloading. 
    display.AddNeopixel( 60, &LATBSET, &LATBCLR, &TRISB, portPin[ 8 ] );
    display.AddNeopixel( 60, &LATBSET, &LATBCLR, &TRISB, portPin[ 9 ] );
    display.AddNeopixel( 60, &LATBSET, &LATBCLR, &TRISB, portPin[ 10 ] );
    
    npAnimation* pAnim;
       
    while ( 1 ) {
        switch ( currAnim ) {            
            case ( ID_AN_CHEVRONS ) :
                pAnim = new anChevrons( &display, 1000, 1 );
                if ( pAnim->Draw() == MODE_PREV ) {
                    currAnim = 1;
                } else {
                    currAnim++;
                }
                delete pAnim;
                break;
            
            case ( ID_AN_COMETS ) :
                pAnim = new anComets( &display, 1000, 1 );
                if ( pAnim->Draw() == MODE_PREV ) {
                    currAnim = 1;
                } else {
                    currAnim++;
                }
                delete pAnim;
                break;
                
            case ( ID_AN_FADEMIDDLE ) :
                pAnim = new anFadeMiddle( &display, 1000, 1 );
                if ( pAnim->Draw() == MODE_PREV ) {
                    currAnim = 1;
                } else {
                    currAnim++;
                }
                delete pAnim;                
                break;
                
            case ( ID_AN_RAIN ) :
                pAnim = new anRain( &display, 1000, 1 );
                if ( pAnim->Draw() == MODE_PREV ) {
                    currAnim = 1;
                } else {
                    currAnim++;
                }
                delete pAnim;
                break;
                
            case ( ID_AN_RAINBOWCHASER ) :
                pAnim = new anRainbowChaser( &display, 1000, 1 );
                if ( pAnim->Draw() == MODE_PREV ) {
                    currAnim = 1;
                } else {
                    currAnim++;
                }
                delete pAnim;
                break;
                                
            case ( ID_AN_CLASSICHORIZ_SA ) :
                pAnim = new anClassicHorizSA( &display, 1000, 1, MODE_REPEAT );
                if ( pAnim->Draw() == MODE_PREV ) {
                    currAnim = 1;
                } else {
                    currAnim++;
                }
                delete pAnim;
                break;
                
            case ( ID_AN_COLORFLOW_SA ) :
                pAnim = new anColorFlowSA( &display, 1000, 1, MODE_REPEAT );
                if ( pAnim->Draw() == MODE_PREV ) {
                    currAnim = 1;
                } else {
                    currAnim++;
                }
                delete pAnim;
                break;
                
            case ( ID_AN_COLORRACE_SA ) :
                pAnim = new anColorRaceSA( &display, 1000, 1, MODE_REPEAT );
                if ( pAnim->Draw() == MODE_PREV ) {
                    currAnim = 1;
                } else {
                    currAnim++;
                }
                delete pAnim;
                break;
                
            case ( ID_AN_PULSEFADE_SA ) :
               pAnim = new anPulseFadeSA( &display, 1000, 1, MODE_REPEAT );
                if ( pAnim->Draw() == MODE_PREV ) {
                    currAnim = 1;
                } else {
                    currAnim++;
                }
                delete pAnim;
                break;
                
            case ( ID_AN_SPLATTER_SA ) :
                pAnim = new anSplatterSA( &display, 1000, 1, MODE_REPEAT );
                if ( pAnim->Draw() == MODE_PREV ) {
                    currAnim = 1;
                } else {
                    currAnim++;
                }
                delete pAnim;
                break;
            
            default : 
                currAnim = 1;
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

extern "C"
void __ISR ( _TIMER_4_VECTOR, IPL7SRS ) TMR4IntHandler( void ) {
    if ( ticks++ == _1_ms_tick ) {
        t2Ticks++;  
        ticks = 0;
    }
    
    if ( analyzerRun ) {
        sampleBuffer[ sampleIndex ].re = ReadADC10( 0 ) - 370 ; // bias voltage at ~1.25V
        sampleBuffer[ sampleIndex ].im = 0;    
        if ( sampleIndex == ( N - 1 ) ) {
            sampleIndex = 0;
        } else {
            sampleIndex++;
        }      
    }
    mT4ClearIntFlag(); 
} 

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

    // Don't care about tx interrupt, return immediately
    if ( mU1TXGetIntFlag() ) {
        mU1TXClearIntFlag();
    }    
}
