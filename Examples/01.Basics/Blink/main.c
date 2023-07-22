//#include "avr/io.h"
#define F_CPU 16000000UL  // 16MHz
#include "util/delay.h"  // _delay_ms()

#define MY_DDRB     (*(volatile unsigned char *)(0x24))
#define MY_PORTB    (*(volatile unsigned char *)(0x25))
#define D13     5  // Port-B bit 6


void setup() {
    //  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
    MY_DDRB |= (1 << D13);  // as Digital OUT
}


int main() {
    setup();

    while( 1 ) {
        MY_PORTB |= (1 << D13);  // set bit is HIGH
        _delay_ms(1000);

        MY_PORTB &= ~(1 << D13);  // clear bit is LOW
        _delay_ms(1000);        
    }
    return 0;
}
