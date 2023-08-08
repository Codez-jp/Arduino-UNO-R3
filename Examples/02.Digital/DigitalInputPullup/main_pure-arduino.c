//#include "avr/io.h"
#define F_CPU 16000000UL  // 16MHz
#include "util/delay.h"  // _delay_ms()


#define INPUT           0
#define OUTPUT          1
#define INPUT_PULLUP    2
#define LOW             0
#define HIGH            1


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
*/
const unsigned char uno_r3_pin_num2str(unsigned char num) {
    static const unsigned char table[] = {
        0, 1, 2, 3, 4, 5, 6, 7,  // D0 - D7
        0, 1, 2, 3, 4, 5,  // D8 - D13
        0, 1, 2, 3, 4, 5   // A0 - A5
    };
    if (num >= 0 && num <= 19) {
        return table[num];
    } else {
        return num;
    }
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


void delay( unsigned long ms ) {
    while( ms-- ) {
        _delay_ms(1);
    }
}


// Digital I/O pin assign
#define LED_BUILTIN     13  // on the board
#define LED             13  // on the breadboard
#define BUZZER          12  // on the breadboard
#define BUTTON          2   // on the breadboard


// #############################################################################
// Arduino IDE
//    [File] - [Examples] - [02.Digital] - [DigitalInputPullup]
// #############################################################################
/*
  Input Pull-up Serial

  This example demonstrates the use of pinMode(INPUT_PULLUP). It reads a digital
  input on pin 2 and prints the results to the Serial Monitor.

  The circuit:
  - momentary switch attached from pin 2 to ground
  - built-in LED on pin 13

  Unlike pinMode(INPUT), there is no pull-down resistor necessary. An internal
  20K-ohm resistor is pulled to 5V. This configuration causes the input to read
  HIGH when the switch is open, and LOW when it is closed.

  created 14 Mar 2012
  by Scott Fitzgerald

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/InputPullupSerial
*/

void setup() {
  //start serial connection
  //Serial.begin(9600);
  //configure pin 2 as an input and enable the internal pull-up resistor
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

}

void loop() {
  //read the pushbutton value into a variable
  int sensorVal = digitalRead(BUTTON);
  //print out the value of the pushbutton
  //Serial.println(sensorVal);

  // Keep in mind the pull-up means the pushbutton's logic is inverted. It goes
  // HIGH when it's open, and LOW when it's pressed. Turn on pin 13 when the
  // button's pressed, and off when it's not:
  if (sensorVal == HIGH) {
    digitalWrite(LED, LOW);
  } else {
    digitalWrite(LED, HIGH);
  }
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
