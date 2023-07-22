//#include "avr/io.h"
#define F_CPU 16000000UL
#include "util/delay.h"  // _delay_ms()

#define MY_DDRB     (*(volatile unsigned char *)(0x24))
#define MY_PORTB    (*(volatile unsigned char *)(0x25))

#define MY_PIND     (*(volatile unsigned char *)(0x29))
#define MY_DDRD     (*(volatile unsigned char *)(0x2a))
#define MY_PORTD    (*(volatile unsigned char *)(0x2b))

#define D13     5  // Port-B bit 6
#define D2      2  // Port-D bit3


void setup( void ) {
    // Blink
    //   https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
    MY_DDRB |= (1 << D13);  // Digital OUT

    // Button
    //   https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button
    // DigitalInputPullup
    //   https://www.arduino.cc/en/Tutorial/BuiltInExamples/InputPullupSerial
    MY_DDRD &= ~(1 << D2);  // as Digital IN
    MY_PORTD |= (1 << D2);  // as PULL-UP
}


int is_bit_set( unsigned char byte, unsigned char bit ) {
    return (byte & (1 << bit)) != 0;
}


int main( void ) {
    setup( );

    while( 1 ) {  // loop
        _delay_ms( 50 );
        if( is_bit_set( MY_PIND, D2 ) ) {
            MY_PORTB &= ~(1 << D13);  // clear as LOW
        }
        else{
            MY_PORTB |= (1 << D13);  // set as HIGH
        }
    }
    return 0;
}