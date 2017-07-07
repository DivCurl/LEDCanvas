#ifndef FFT_H
#define	FFT_H

#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include <plib.h>
#include <fftc.h>
#include <cmath>

/*
#define fftc fft16c256
#define N 256
 */

#define fftc fft16c128
#define N 128

/*
#define fftc fft16c64
#define N 64
 */

#define AN_ADC_FLOOR    0
#define AN_ADC_CEILING  1024

void ComputeFFT();

#endif
