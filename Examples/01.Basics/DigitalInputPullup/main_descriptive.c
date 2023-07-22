//#include "avr/io.h"
#define F_CPU 16000000UL
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

#define MY_PORTD    (*(volatile unsigned char *)(0x2b))
#define MY_DDRD     (*(volatile unsigned char *)(0x2a))
#define MY_PIND     (*(volatile unsigned char *)(0x29))

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
* PORTD(The port D Data Register)
* BIT 7   6   5   4   3   2   1   0
* R/W 0   0   0   0   0   0   0   0   | 0/1 = LOW/HIGH
*     |   |   |   |   |   |   |   |
* PIN D7  D6  D5  D4  D3  D2  Tx  Rx
*     |   |   |   |   |   |   |   |
* DDRD(The port D Data Direction Register)
* BIT 7   6   5   4   3   2   1   0
* R/W 0   0   0   0   0   0   0   0   | 0/1 = Input/Output
*     |   |   |   |   |   |   |   |
* PIN D7  D6  D5  D4  D3  D2  Tx  Rx
*     |   |   |   |   |   |   |   |
* PIND(The port D Input pins address)
* BIT 7   6   5   4   3   2   1   0
* R/W 0   0   0   0   0   0   0   0   | 0/1 = Pull-Down/Pull-Up
*     |   |   |   |   |   |   |   |
* PIN D7  D6  D5  D4  D3  D2  Tx  Rx
*                         |
*                         +-+--> Tactical Switch
*/
#define PD7 BIT7
#define PD6 BIT6
#define PD5 BIT5
#define PD4 BIT4
#define PD3 BIT3
#define PD2 BIT2
#define PD1 BIT1
#define PD0 BIT0

#define D7 PD7  // Port-D bit 7
#define D6 PD6  // Port-D bit 6
#define D5 PD5  // Port-D bit 5
#define D4 PD4  // Port-D bit 4
#define D3 PD3  // Port-D bit 3
#define D2 PD2  // Port-D bit 2


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
        _delay_ms(50);
        if( is_bit_set( MY_PIND, D2 ) ) {
            MY_PORTB &= ~(1 << D13);  // clear as LOW
        }
        else{
            MY_PORTB |= (1 << D13);  // set as HIGH
        }
    }
    return 0;
}