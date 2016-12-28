#include "io.h"

int uartBytesRead;
bool isReadPacket;
uint64_t lcdReadBuffer;
gModes_t globalMode;

extern "C"
void LCDReadByte() {
    // get most recent byte out of UART buffer
    uint64_t rxByte = ReadUART1();

    // if we get an ACK or NAK response, return immediately. Note this would only happen following a send message
    if ( uartBytesRead == 0 && ( ( rxByte == LCD_ACK ) || ( rxByte == LCD_NAK ) ) ) {
        return;
    }

    // Was a full data packet previously read? 
    if ( ( uartBytesRead == 6 ) ) {
        isReadPacket = 0;
        uartBytesRead = 0;
        lcdReadBuffer = 0;
    }

    // if first byte read and is response to query (byte 0 value is 0x1 or 0x7), flag it as packet header
    if ( ( uartBytesRead == 0) && ((rxByte == 0x01) ||  ( rxByte == 0x07 ) ) ) {
        isReadPacket = 1;
    }

    // continue reading packets after packet header found...
    if ( isReadPacket ) {
        lcdReadBuffer = ( lcdReadBuffer << 8 ) | rxByte;
        uartBytesRead++;
    }
}

void LCDSendMessage( const uint64_t msg, int len ) {
    // sends out packet bytes on UART depending on
    // packet buffer length (between 1 and 6 bytes)
    if ( len >= 6 ) {
        putcUART1( (char)( ( msg >> 40 ) & 0xff ) );
    }
    if ( len >= 5 ) {
        putcUART1( (char)( ( msg >> 32 ) & 0xff ) );
    }
    if ( len >= 4 ) {
        putcUART1( (char)( ( msg >> 24 ) & 0xff ) );
    }
    if ( len >= 3 ) {
        putcUART1( (char)( ( msg >> 16 ) & 0xff ) );
    }
    if ( len >= 2 ) {
        putcUART1( (char)( ( msg >> 8 ) & 0xff ) );
    }
    if ( len >= 1 ) {
        putcUART1( (char)( ( msg  ) & 0xff ) );
    }
}
