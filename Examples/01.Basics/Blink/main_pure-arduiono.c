//#include "avr/io.h"
#define F_CPU 16000000UL  // 16MHz
#include "util/delay.h"  // _delay_ms()


#define INPUT           0
#define OUTPUT          1
#define INPUT_PULLUP    2
#define LOW             0
#define HIGH            1

#define BIT0    0
#define BIT1    1
#define BIT2    2
#define BIT3    3
#define BIT4    4
#define BIT5    5
#define BIT6    6
#define BIT7    7


// PORTD – Port D Data Register
#define MY_PORTD    (*(volatile unsigned char *)(0x2B))
// DDRD – Port D Data Direction Register
#define MY_DDRD     (*(volatile unsigned char *)(0x2A))
// PIND – Port D Input Pins Address
#define MY_PIND     (*(volatile unsigned char *)(0x29))

// PORTB – Port B Data Register
#define MY_PORTB    (*(volatile unsigned char *)(0x25))
// DDRB – Port B Data Direction Register
#define MY_DDRB     (*(volatile unsigned char *)(0x24))
// PINB – Port B Input Pins Address
#define MY_PINB     (*(volatile unsigned char *)(0x23))

// PORTC – Port C Data Register
#define MY_PORTC    (*(volatile unsigned char *)(0x28))
// DDRC – Port C Data Direction Register
#define MY_DDRC     (*(volatile unsigned char *)(0x27))
// PINC – Port C Input Pins Address
#define MY_PINC     (*(volatile unsigned char *)(0x26))

// ADCSRA – ADC Control and Status Register A
#define MY_ADCSRA   (*(volatile unsigned char *)(0x7A))
// ADCSRB – ADC Control and Status Register B
#define MY_ADCSRB   (*(volatile unsigned char *)(0x7B))
// ADMUX – ADC Multiplexer Selection Register
#define MY_ADMUX    (*(volatile unsigned char *)(0x7C))
// ADCW – ADC Data Register CAUTION : ADCW is not an official word size definition
#define MY_ADCW     (*(volatile unsigned short *)(0x78))


// port D
#define D0   0
#define D1   1
#define D2   2
#define D3   3
#define D4   4
#define D5   5
#define D6   6
#define D7   7
// port B
#define D8   8
#define D9   9
#define D10  10
#define D11  11
#define D12  12
#define D13  13
// port C
#define A0  14
#define A1  15
#define A2  16
#define A3  17
#define A4  18
#define A5  19


/*
* PORTD(The port D Data Register)
* BIT  7   6   5   4   3   2   1   0
* R/W  0   0   0   0   0   0   0   0   |   0/1 = (TRI_STATE/INPUT_PULLUP)/(LOW/HIGH)
* DDRD(The port D Data Direction Register)
* BIT  7   6   5   4   3   2   1   0
* R/W  0   0   0   0   0   0   0   0   |   0/1 = INPUT/OUTPUT
*      |   |   |   |   |   |   |   |
* SILK D7  D6  D5  D4  D3  D2  D1TXD0RX
* PIN  7   6   5   4   3   2   1   0
*                                  |
*                                  +-+--> BUTTON
*
* PORTB(The port B Data Register)
* BIT  7   6   5   4   3   2   1   0
* R/W  -   -   0   0   0   0   0   0   |   0/1 = LOW/HIGH
* DDRB(The port B Data Direction Register)
* BIT  7   6   5   4   3   2   1   0
* R/W  -   -   0   0   0   0   0   0   |   0/1 = INPUT/OUTPUT
*              |   |   |   |   |   |
* SILK -   -   D13 D12 D11 D10 D9  D8
* OIN  -   -   13  12  11  10  9   8 
*              |   |
*              |   +-+--> BUZZER
*              +-+--> LED
*
* PORTC(The port C Data Register)
* BIT  7   6   5   4   3   2   1   0
* R/W  -   -   0   0   0   0   0   0   |   0/1 = LOW/HIGH
* DDRC(The port C Data Direction Register)
* BIT  7   6   5   4   3   2   1   0
* R/W  -   -   0   0   0   0   0   0   |   0/1 = INPUT/OUTPUT
*              |   |   |   |   |   |
* SILK -   -   A5  A4  A3  A2  A1  A0
* PIN  -   -   19  18  17  16  15  14
*              |   |   |   |   |   |
*              NC  NC  NC  NC  NC  NC <-- only digital I/O
*
* ADCSRA(The ADC Control and Status Register A)
*   ADPS<2:0>(3) <- ADC, prescaler
*   ADIE<3> <- Interrupt enable
*   ADIF<4> <- Interrupt flag
*   ADATE<5> <- Auto trigger enable
*   ADSC<6> <- Start conversion
*   ADEN<7> <- Enable ADC
*
* ADCSRB(The ADC Control and Status Register B)
*   ADTS<2:0>(3) <- Auto trigger source
*
* ADMUX(The ADC Multiplexer Selection Register)
*   MUX<3:0>(4) <- ADC0 as input channel
*   ADLAR<5> <- Right adjust result
*   REFS<7:6>(2) <- AVCC as reference voltage
*
*/


const unsigned char uno_r3_pin_num2str(unsigned char num) {
    static const unsigned char table[] = {
        0, 1, 2, 3, 4, 5, 6, 7,  // D0 - D7
        0, 1, 2, 3, 4, 5,  // D8 - D13
        0, 1, 2, 3, 4, 5   // A0 - A5
    };
    if (num >= 0 && num <= 19) {
        return table[num];
    }
    return 0;
}


void pinMode( unsigned char pin, unsigned char mode ) {
    if( pin>=0 && pin<=7 ) {
        pin = uno_r3_pin_num2str(pin);
        if( mode == OUTPUT ) {
            MY_DDRD |= (1 << pin);  // as Output
        }
        else if( mode == INPUT_PULLUP ) {
            MY_DDRD &= ~(1 << pin);  // as Input
            MY_PORTD |= (1 << pin);  // as PULL-UP
        }
        else{
            MY_DDRD &= ~(1 << pin);  // as Input
        }
    }
    else if( pin>=8 && pin<=13 ) {
        pin = uno_r3_pin_num2str(pin);
        if( mode == OUTPUT ) {
            MY_DDRB |= (1 << pin);  // as Output
        }
        else if( mode == INPUT_PULLUP ) {
            MY_DDRB &= ~(1 << pin);  // as Input
            MY_PORTB |= (1 << pin);  // as PULL-UP
        }
        else{
            MY_DDRB &= ~(1 << pin);  // as Input
        }
    }
    else if( pin>=14 && pin<=19 ) {
        pin = uno_r3_pin_num2str(pin);
        if( mode == OUTPUT ) {
            MY_DDRC |= (1 << pin);  // as Output
        }
        else if( mode == INPUT_PULLUP ) {
            MY_DDRC &= ~(1 << pin);  // as Input
            MY_PORTC |= (1 << pin);  // as PULL-UP
        }
        else{
            MY_DDRC &= ~(1 << pin);  // as Input
        }
    }
}


void digitalWrite( unsigned char pin, unsigned char value ) {
    if( pin>=0 && pin<=7 ) {
        pin = uno_r3_pin_num2str(pin);
        if( value == HIGH ) {
            MY_PORTD |= (1 << pin);  // set bit is HIGH
        }
        else{
            MY_PORTD &= ~(1 << pin);  // clear bit is LOW
        }
    }
    else if( pin>=8 && pin<=13 ) {
        pin = uno_r3_pin_num2str(pin);
        if( value == HIGH ) {
            MY_PORTB |= (1 << pin);  // set bit is HIGH
        }
        else{
            MY_PORTB &= ~(1 << pin);  // clear bit is LOW
        }
    }
    else if( pin>=14 && pin<=19 ) {
        pin = uno_r3_pin_num2str(pin);
        if( value == HIGH ) {
            MY_PORTC |= (1 << pin);  // set bit is HIGH
        }
        else{
            MY_PORTC &= ~(1 << pin);  // clear bit is LOW
        }
    }
}


unsigned char digitalRead( unsigned char pin ) {
    if( pin>=0 && pin<=7 ) {
        pin = uno_r3_pin_num2str(pin);
        return (MY_PIND & (1 << pin)) != 0;
    }
    else if( pin>=8 && pin<=13 ) {
        pin = uno_r3_pin_num2str(pin);
        return (MY_PINB & (1 << pin)) != 0;
    }
    else if( pin>=14 && pin<=19 ) {
        pin = uno_r3_pin_num2str(pin);
        return (MY_PINC & (1 << pin)) != 0;
    }
    return 0;
}


int analogRead( unsigned char pin ) {
    if( pin>=14 && pin<=19 ) {
        pin = uno_r3_pin_num2str(pin);
        MY_ADMUX = (MY_ADMUX & 0b11110000) | pin;  // pin as input channel
        MY_ADMUX &= ~(1 << BIT5);  // 0: Right adjust result
        MY_ADMUX |= (1 << BIT6);  // 1: AVCC as reference voltage
        MY_ADMUX &= ~(1 << BIT7);  // 0: AVCC as reference voltage
//        MY_ADMUX = 0b01000000;  // AVCC as reference voltage, ADC0 as input channel
        MY_ADCSRA |= (1 << BIT7);  // 1: Enable ADC
        MY_ADCSRA |= (1 << BIT2);  // 1: prescaler = 128
        MY_ADCSRA |= (1 << BIT1);  // 1: prescaler = 128
        MY_ADCSRA |= (1 << BIT0);  // 1: prescaler = 128
//        MY_ADCSRA = 0b10000111;  // Enable ADC, prescaler = 128

        MY_ADCSRA |= (1 << BIT6);  // Start conversion
        while (MY_ADCSRA & (1 << BIT6));  // Wait for conversion to complete
        return MY_ADCW;  // Return result
    }
    return 0;
}


void delay( unsigned long ms ) {
    while( ms-- ) {
        _delay_ms(1);
    }
}


// Digital I/O pin assign
#define LED_BUILTIN     D13  // on the board
#define LED             D13  // on the breadboard
#define BUZZER          D12  // on the breadboard
#define BUTTON          D2  // on the breadboard
#define VR              A0  // on the breadboard


// #############################################################################
// Arduino IDE
//    [File] - [Examples] - [01.Basics] - [Blink]
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
