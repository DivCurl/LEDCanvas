#ifndef FFT_H
#define	FFT_H

#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include <plib.h>
#include <fftc.h>
#include <cmath>
#include <cstdint>

#define ADC_SAMPLE_FREQ ( 20000 ) 
#define FFT_128

#ifdef FFT_1024
    #define N 1024
    #define fftc fft16c1024
#endif

#ifdef FFT_256
    #define N 256	
    #define fftc fft16c256
#endif

#ifdef FFT_128
    #define N 128
    #define fftc fft16c128
#endif

#ifdef FFT_64
    #define N 64
    #define fftc fft16c64
#endif

static const int16_t ADC_COUNT_NOISE = 25;      // about 100mV (~30 ADC counts) noise threshold as measured by scope
static const int16_t ADC_COUNT_1V = 310;
static const int16_t ADC_COUNT_BIAS = 388;      // 1.25V DC bias (388 counts); 1.2V actual measured with scope
static const int16_t ADC_COUNT_VMAX = 698;      // 1.25V (bias) + 1V   
static const int16_t ADC_COUNT_VMIN = 78;       // 1.25V (bias) - 1V   
static const int16_t ADC_COUNT_ZERO = ADC_COUNT_BIAS - ADC_COUNT_VMIN;

void InitFFT();
void ComputeFFT();

#endif
