# LEDCanvas
A project to control Adafruit's "Neopixel" LED strips with a 80MHz PIC32 MCU. I was motivated to do this because I am not inclined to learn the Arduino platform on which most of Adafruit's sample code is based. 

The design is with flexibility kept in mind: any number of strips can be connected to the PIC32 up to the number of pins on a given port. The strips can be cut to whatever length, which only requires the programmer to specify the number of LEDs on each connected strip. The project will build a rectangular display based on the largest strip length connected and will simply clip out any pixels that aren't visible if variable-length strips were to be connected (I can't see a reason why anybody would want to do that, but hey...people do weird shit). Note that, since the interface and wiring is so simple, the implementation of the electronics is not specified or discussed here, but I will point out that since the PIC32 is a 3V3 device and the Neopixels run on 4-5V be mindful of giving the PIC32 its own clean 3V3 rail. I will also mention that I did not have to buffer the 3V3 outputs on the PIC up to 5V for the Neopixels. I did initially order some buffers but found that the Neopixels did not require them in my setup. Your mileage may vary...

There are several pre-written animations of my own design already included which run out of the box (see descriptions below). It was a primary motiviation to have several animations react to music, so the project is configured for an amplified electret mic to be connected to an analog input (currently hard-coded to AI15) for doing the spectrum analyzer FFTs. The gain levels are custom-tuned to the mic I used, but can be changed as needed. A line-level out from an audio player could be easily worked in in lieu of a mic with some tweaking. 

I have also hard-coded support for a 4D-Systems LCD touchscreen which allows adjusting various parameters of the animations and display at runtime (display brightness, next, previous, fade times, dB gain for the spectrum analyzers, etc.) This could easily be adapted to any remote serial-based host (e.g. a PC or laptop, bluetooth, etc.) connected to the UART. 

BASIC CODE AND LAYOUT NOTES:

1. Each animation is defined in its own source file ("an" prefix on soure code file).

2. All primitive drawing functions are provided by the npAnimation class, which each animation inherits. 

3. All low-level drawing functions including framebuffer handling and the main refresh loop are provided by the npDisplay class.

4. All initialization is handled in main.cpp right in main(), including setting number of connected strips and their respective LED
counts, setting up the display, building the animation lists and specyfing their options, etc. 

5. The display is not multiplexed so each frame is drawn in full and the main animation loop runs continously. Interrupts are kept as mean and lean as possible to avoid impacting the critical-time refresh loop (npDisplay::Refresh). A T4 timer interrupt is used for accurate delays and reads/writes via the UART are handled via interrupts also. 

CURRENT ANIMATIONS:
1. anChevrons: dropping Chevrons with progressive fading color gradient
2. anRainbowChaser: alternating stripes of moving, rainbow-faded colors
3. anComets: small dots which move orthogonally around the display which leave fading tails (quantity, speed, direction, and color are randomized)
4. anRain: drops falling from top of display, with color slowing fading around the color wheel
5. anFadeMiddle: similar to Rainbow Chaswer, but brightness decreases on each strip towards the middle 
6. anClassicSA: my take on a classic audio spectrum analyzer
7. anPulseFadeSA: simple spectrum analyzer which fades out with each frame giving a strobe effect
8. anSplatterSA: spectrum analyzer which draws 'splats' (dots) in random positions on each spectral line, with the number of splats being driven by the audio.
9. anColorFlowSA: spectrum analyzer that draws a continuous stream of color upwards, with the color's change being driven by the audio
10. anColorRaceSA: similar to Color Flow, but the color streams being 'stepped' by the audio rather than continuously streamed and faded.

TODO: 
1. Optimize some of the more expensive loops, if possible (impetus to learn MIPS assembly)

2. Better randomization and external interfacing options. Currently is designed to interface to touchscreen via UART but would be nice to extend this to WIFI or something. 

ANIMATION TODO:
1. Implement Tetris, with audio driving the speed and rotation of the pieces
2. Sprites: since I've recently added a pixel class, I'd like to see about creating some sprites and maybe basic animations

