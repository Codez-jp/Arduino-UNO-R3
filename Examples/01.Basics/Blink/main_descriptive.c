//#include "avr/io.h"
#define F_CPU 16000000UL  // 16MHz
#include "util/delay.h"  // _delay_ms()

#define BIT7 7  // just bit 7
#define BIT6 6  // just bit 6
#define BIT5 5  // just bit 5
#define BIT4 4  // just bit 4
#define BIT3 3  // just bit 3
#define BIT2 2  // just bit 2
#define BIT1 1  // just bit 1
#define BIT0 0  // just bit 0

/* ====================================== */
/* DIGITAL Input/Output control registers */
/* ====================================== */
#define MY_PORTB    (*(volatile unsigned char *)(0x25))
#define MY_DDRB     (*(volatile unsigned char *)(0x24))

#define PB5 BIT5
#define PB4 BIT4
#define PB3 BIT3
#define PB2 BIT2
#define PB1 BIT1
#define PB0 BIT0

#define D13 PB5  // Port-B bit 5
#define D12 PB4  // Port-B bit 4
#define D11 PB3  // Port-B bit 3
#define D10 PB2  // Port-B bit 2
#define D9  PB1  // Port-B bit 1
#define D8  PB0  // Port-B bit 0

/*
* PORTB(The port B Data Register)
* BIT 7   6   5   4   3   2   1   0
* R/W -   -   0   0   0   0   0   0   | 0/1 = LOW/HIGH
*             |   |   |   |   |   |
* PIN -   -   D13 D12 D11 D10 D9  D8
*             |   |   |   |   |   |
* DDRB(The port B Data Direction Register)
* BIT 7   6   5   4   3   2   1   0
* R/W -   -   0   0   0   0   0   0   | 0/1 = Input/Output
*             |   |   |   |   |   |
* PIN -   -   D13 D12 D11 D10 D9  D8 
*             |   |
*             |   +-+--> BUZZER
*             +-+--> LED
*/

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
