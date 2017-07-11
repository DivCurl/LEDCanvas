#ifndef FFT_H
#define	FFT_H

#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include <plib.h>
#include <fftc.h>
#include <cmath>

#define ADC_SAMPLE_FREQ ( 20000 ) 
#define FFT_256

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

#define AN_ADC_FLOOR    0
#define AN_ADC_CEILING  1024

void InitFFT();
void ComputeFFT();

#endif
