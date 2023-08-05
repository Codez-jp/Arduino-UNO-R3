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

// PORTB – Port B Data Register
#define MY_PORTB    (*(volatile unsigned char *)(0x25))
// DDRB – Port B Data Direction Register
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
* BIT  7   6   5   4   3   2   1   0
* R/W  -   -   0   0   0   0   0   0   |   0/1 = LOW/HIGH
* PIN  -   -   D13 D12 D11 D10 D9  D8
*              |   |   |   |   |   |
* DDRB(The port B Data Direction Register)
* BIT  7   6   5   4   3   2   1   0
* R/W  -   -   0   0   0   0   0   0   |   0/1 = Input/Output
* PIN  -   -   D13 D12 D11 D10 D9  D8 
*              |   |
*              |   +-+--> BUZZER
*              +-+--> LED
*/
#define OUTPUT  1
#define INPUT   0
#define HIGH    1
#define LOW     0

#define LED_BUILTIN     D13  // on the board
#define LED             D13  // on the breadboard
#define BUZZER          D12  // on the breadboard


void pinMode( unsigned char pin, unsigned char mode ) {
    if( mode == OUTPUT ) {
        MY_DDRB |= (1 << pin);  // as Output
    }
    else{
        MY_DDRB &= ~(1 << pin);  // as Input
    }
}


void digitalWrite( unsigned char pin, unsigned char value ) {
    if( value == HIGH ) {
        MY_PORTB |= (1 << pin);  // set bit is HIGH
    }
    else{
        MY_PORTB &= ~(1 << pin);  // clear bit is LOW
    }
}


void delay( unsigned long ms ) {
    while( ms-- ) {
        _delay_ms(1);
    }
}


/* Arduino IDE
*   [File] - [Examples] - [01.Basics] - [Blink]
*     https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/
// #############################################################################
// #############################################################################
/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
// #############################################################################
// #############################################################################


int main() {
    setup();
    while( 1 ) {
        loop();     
    }
    return 0;
}
