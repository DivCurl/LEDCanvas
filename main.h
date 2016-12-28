#ifndef MAIN_H
#define	MAIN_H

#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include <cstdlib>
#include <vector>
#include <p32xxxx.h>
#include <plib.h>  
#include <xc.h>
#include <sys/attribs.h>
#include "io.h"
#include "npDisplay.h"
#include "anTest.h"
#include "anAnalyzers.h"
#include "anPatterns.h"
#include "anStrobes.h"

// all code is tuned to run on a PIC32 with 80 MHz core clock. 
// Do not change nor attempt to use with slower PIC32 MCUs!
#define SYS_FREQ    ( 80000000L )   

// Stuff for ADC config.
#define ADC_CONFIG1 ( ADC_MODULE_ON | ADC_FORMAT_INTG | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON )
#define ADC_CONFIG2 ( ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_ON | ADC_SAMPLES_PER_INT_1 | ADC_ALT_BUF_OFF | ADC_ALT_INPUT_OFF )
#define ADC_CONFIG3 ( ADC_CONV_CLK_INTERNAL_RC | ADC_SAMPLE_TIME_15 )
#define ADC_CONFIGPORT ( ENABLE_AN15_ANA )

// Signal wired to AN15, skip all others for faster sampling.
#define ADC_CONFIGSCAN (                                                \
    SKIP_SCAN_AN0 | SKIP_SCAN_AN1 | SKIP_SCAN_AN2 | SKIP_SCAN_AN3 |     \
    SKIP_SCAN_AN4 | SKIP_SCAN_AN5 | SKIP_SCAN_AN6 | SKIP_SCAN_AN7 |     \
    SKIP_SCAN_AN8 | SKIP_SCAN_AN9 | SKIP_SCAN_AN10 | SKIP_SCAN_AN11 |   \
    SKIP_SCAN_AN12 | SKIP_SCAN_AN13 | SKIP_SCAN_AN14                    \
    )

#define UARTCONFIG1 (           \
    UART_EN |                   \
    UART_IDLE_CON |             \
    UART_RX_TX |                \
    UART_DIS_WAKE |             \
    UART_DIS_LOOPBACK |         \
    UART_DIS_ABAUD |            \
    UART_NO_PAR_8BIT |          \
    UART_1STOPBIT |             \
    UART_IRDA_DIS |             \
    UART_DIS_BCLK_CTS_RTS |     \
    UART_NORMAL_RX |            \
    UART_BRGH_SIXTEEN           \
    )

// define setup config #2 for OpenUARTx
#define UARTCONFIG2 (           \
    UART_TX_PIN_LOW |           \
    UART_RX_ENABLE |            \
    UART_TX_ENABLE |            \
    UART_INT_TX |               \
    UART_INT_RX_CHAR |          \
    UART_ADR_DETECT_DIS |       \
    UART_RX_OVERRUN_CLEAR       \
    )

void InitADC( void );
void InitUART( void );
void InitLCD( void );

#endif

