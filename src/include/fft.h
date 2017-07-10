#ifndef FFT_H
#define	FFT_H

#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include <plib.h>
#include <fftc.h>
#include <cmath>

#define ADC_SAMPLE_FREQ ( 20000 ) 

#define FFT_256

#ifdef FFT_256
    #define N 256	// Also change the log2N variable below!!
    #define fftc fft16c256 //from fftc.h, for N = 256 use fft16c256, for N = 1024 use fft16c1024
#endif

#ifdef FFT_128
    #define N 128	// Also change the log2N variable below!!
    #define fftc fft16c128 //from fftc.h, for N = 256 use fft16c256, for N = 1024 use fft16c1024
#endif

#ifdef FFT_64
    #define N 64	// Also change the log2N variable below!!
    #define fftc fft16c64 //from fftc.h, for N = 256 use fft16c256, for N = 1024 use fft16c1024
#endif

#define AN_ADC_FLOOR    0
#define AN_ADC_CEILING  1024

void InitFFT();
void ComputeFFT();

#endif
