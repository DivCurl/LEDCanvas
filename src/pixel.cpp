

 // calculate scaled brightness relative to global brightness
/*
pixel::Set( rgb_t clr, int brt ) {
    uint16_t scaledBrt = (float)brt / 255 * pDisplay->globalBrightness;
    uint16_t index;
    
    if ( pDisplay != NULL ) {
        if ( ( index = pDisplay->GetColorArrayIndex( x, y ) ) >= 0 ) {  // returns -1 if coords are out of bounds
            pDisplay->frameBuffer[ index ] = ( color.g * ( scaledBrt + 1 ) ) >> 8;
            pDisplay->frameBuffer[ index + 1 ] = ( color.r * ( scaledBrt + 1 ) ) >> 8;
            pDisplay->frameBuffer[ index + 2 ] = ( color.b * ( scaledBrt + 1 ) ) >> 8;
            pDisplay->frameBuffer[ index + 3 ] = ( color.w * ( scaledBrt + 1 ) ) >> 8;
        }
    }
    
}
*/
