# LEDCanvas
A project to control Adafruit's "Neopixel" LED strips with a 80MHz PIC32 MCU. I was motivated to do this because I am not inclined to learn the Arduino platform on which most of Adafruit's sample code is based. 

The design is with flexibility kept in mind: any number of strips can be connected to the PIC32 up to the number of pins on a given port. The strips can be cut to whatever length, which only requires the programmer to specify the number of LEDs on each connected strip. The project will build a rectangular display based on the largest strip length connected and will simply clip out any pixels that aren't visible if variable-length strips were to be connected (I can't see a reason why anybody would want to do that, but hey...people do weird shit). Note that, since the interface and wiring is so simple, the implementation of the electronics is not specified or discussed here, but I will point out that since the PIC32 is a 3V3 device and the Neopixels run on 4-5V be mindful of giving the PIC32 its own clean 3V3 rail. I will also mention that I did not have to buffer the 3V3 outputs on the PIC up to 5V for the Neopixels. I did initially order some buffers but found that the Neopixels did not require them in my setup. Your mileage may vary...

There are several pre-written animations of my own design already included which run out of the box. It was a primary motiviation to have several animations react to music, so the project is configured for an amplified electret mic to be connected to an analog input (currently hard-coded to AI15) for doing the spectrum analyzer FFTs. The gain levels are custom-tuned to the mic I used, but can be changed as needed. 

I have also hard-coded support for a 4D-Systems LCD touchscreen which allows adjusting various parameters of the animations and display at runtime (display brightness, next, previous, fade times, dB gain for the spectrum analyzers, etc.) This could easily be adapter to any remote serial-based host (e.g. a PC or laptop, bluetooth, etc.) connected to the UART. 

Basic Code Layout Notes:

1. All animations are defined in their respective 'animation type' source file: anPatterns, anAnalyzers, anStrobes, etc. (see TODOs).

2. All primitive drawing functions are provided in npAnimation.cpp, which each animation inherits. 

3. All low-level drawing functions including framebuffer handling and the main refresh loop are provided in npDisplay.cpp.

4. All initialization is handled in main.cpp right in main(), including setting number of connected strips and their respective LED
counts, setting up the display, building the animation lists and specyfing their options, etc. 

5. The display is not multiplexed so each frame is drawn in full and the main animation loop runs continously. Interrupts are kept to a minimum to avoid impacting the critical-time refresh loop (npDisplay::Refresh) - a timer interrupt is used for accurate delays and reads/writes via the UART are handled via interrupts also. 

TODO: 

1. Split each animation into its own class and remove the anPatterns, anAnalyzers...etc...'animation type' classes. Animations will no longer be stored in 'type' vectors as currently occurs in main(). The decision to do this ended up with each type class looking bloated and overall shitty. 

2. Organize source code files in subdirectories. 

3. Optimize some of the more expensive loops, if possible

Build History:

1. Initial commit, tested with 9 strips (9 strips * 60 LEDs per strip * 4 pixels per LED [RGBW] = 2160 pixels total). 
