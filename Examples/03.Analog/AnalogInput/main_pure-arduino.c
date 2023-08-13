//#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL  // 16MHz
#include "util/delay.h"  // _delay_ms()


#define INPUT           0
#define OUTPUT          1
#define INPUT_PULLUP    2
#define LOW             0
#define HIGH            1
#define OFF             0
#define ON              1
#define LEVEL           0
#define CHANGE          1
#define FALLING         2
#define RISING          3


#define BIT0    0
#define BIT1    1
#define BIT2    2
#define BIT3    3
#define BIT4    4
#define BIT5    5
#define BIT6    6
#define BIT7    7


// PORTD - Port D Data Register
#define MY_PORTD    (*(volatile unsigned char *)(0x2B))
// DDRD - Port D Data Direction Register
#define MY_DDRD     (*(volatile unsigned char *)(0x2A))
// PIND - Port D Input Pins Address
#define MY_PIND     (*(volatile unsigned char *)(0x29))

// PORTB - Port B Data Register
#define MY_PORTB    (*(volatile unsigned char *)(0x25))
// DDRB - Port B Data Direction Register
#define MY_DDRB     (*(volatile unsigned char *)(0x24))
// PINB - Port B Input Pins Address
#define MY_PINB     (*(volatile unsigned char *)(0x23))

// PORTC - Port C Data Register
#define MY_PORTC    (*(volatile unsigned char *)(0x28))
// DDRC - Port C Data Direction Register
#define MY_DDRC     (*(volatile unsigned char *)(0x27))
// PINC - Port C Input Pins Address
#define MY_PINC     (*(volatile unsigned char *)(0x26))

// ADCSRA - ADC Control and Status Register A
#define MY_ADCSRA   (*(volatile unsigned char *)(0x7A))
// ADCSRB - ADC Control and Status Register B
#define MY_ADCSRB   (*(volatile unsigned char *)(0x7B))
// ADMUX - ADC Multiplexer Selection Register
#define MY_ADMUX    (*(volatile unsigned char *)(0x7C))
// ADCW - ADC Data Register CAUTION : ADCW is not an official word size definition
#define MY_ADCW     (*(volatile unsigned short *)(0x78))

// EICRA - External Interrupt Control Register A
#define MY_EICRA    (*(volatile unsigned char *)(0x69))
// EICRB - External Interrupt Control Register B
#define MY_EICRB    (*(volatile unsigned char *)(0x6A))
// EIMSK - External Interrupt Mask Register
#define MY_EIMSK    (*(volatile unsigned char *)(0x3D))
// EIFR - External Interrupt Flag Register
#define MY_EIFR     (*(volatile unsigned char *)(0x3C))

// TCCR1A - Timer/Counter1 Control Register A
#define MY_TCCR1A   (*(volatile unsigned char *)(0x80))
// TCCR1B - Timer/Counter1 Control Register B
#define MY_TCCR1B   (*(volatile unsigned char *)(0x81))
// OCR1A - Timer/Counter1 Output Compare Register A
#define MY_OCR1A    (*(volatile unsigned short *)(0x88))
// TIMSK1 - Timer/Counter1 Interrupt Mask Register
#define MY_TIMSK1   (*(volatile unsigned char *)(0x6F))
// TIFR1 - Timer/Counter1 Interrupt Flag Register
#define MY_TIFR1    (*(volatile unsigned char *)(0x36))


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
*/
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

// Port D
#define MY_PD0  0
#define MY_PD1  1
#define MY_PD2  2
#define MY_PD3  3
#define MY_PD4  4
#define MY_PD5  5
#define MY_PD6  6
#define MY_PD7  7
// Port B
#define MY_PB0  0
#define MY_PB1  1
#define MY_PB2  2
#define MY_PB3  3
#define MY_PB4  4
#define MY_PB5  5
// Port C
#define MY_PC0  0
#define MY_PC1  1
#define MY_PC2  2
#define MY_PC3  3
#define MY_PC4  4
#define MY_PC5  5

const unsigned char uno_r3_pin_num2bit(unsigned char num) {
    static const unsigned char table[] = {
        MY_PD0, MY_PD1, MY_PD2, MY_PD3, MY_PD4, MY_PD5, MY_PD6, MY_PD7, // D0 - D7
        MY_PB0, MY_PB1, MY_PB2, MY_PB3, MY_PB4, MY_PB5,                 // D8 - D13
        MY_PC0, MY_PC1, MY_PC2, MY_PC3, MY_PC4, MY_PC5                  // A0 - A5
    };
    if (num >= D0 && num <= A5) {
        return table[num];
    }
    // default
    return D0;
}


void pinMode( unsigned char pin, unsigned char mode ) {
    unsigned char bit_per_port = uno_r3_pin_num2bit(pin);
    // Port D
    if( pin>=D0 && pin<=D7 ) {
        if( mode == OUTPUT ) {
            MY_DDRD |= (1 << bit_per_port);  // as Output
        }
        else if( mode == INPUT_PULLUP ) {
            MY_DDRD &= ~(1 << bit_per_port);  // as Input
            MY_PORTD |= (1 << bit_per_port);  // as PULL-UP
        }
        else{
            MY_DDRD &= ~(1 << bit_per_port);  // as Input
        }
    }
    // Port B
    else if( pin>=D8 && pin<=D13 ) {
        if( mode == OUTPUT ) {
            MY_DDRB |= (1 << bit_per_port);  // as Output
        }
        else if( mode == INPUT_PULLUP ) {
            MY_DDRB &= ~(1 << bit_per_port);  // as Input
            MY_PORTB |= (1 << bit_per_port);  // as PULL-UP
        }
        else{
            MY_DDRB &= ~(1 << bit_per_port);  // as Input
        }
    }
    // Port C
    else if( pin>=A0 && pin<=A5 ) {
        if( mode == OUTPUT ) {
            MY_DDRC |= (1 << bit_per_port);  // as Output
        }
        else if( mode == INPUT_PULLUP ) {
            MY_DDRC &= ~(1 << bit_per_port);  // as Input
            MY_PORTC |= (1 << bit_per_port);  // as PULL-UP
        }
        else{
            MY_DDRC &= ~(1 << bit_per_port);  // as Input
        }
    }
}


void digitalWrite( unsigned char pin, unsigned char value ) {
    unsigned char bit_per_port = uno_r3_pin_num2bit(pin);
    // Port D
    if( pin>=D0 && pin<=D7 ) {
        if( value == HIGH ) {
            MY_PORTD |= (1 << bit_per_port);  // set bit is HIGH
        }
        else{
            MY_PORTD &= ~(1 << bit_per_port);  // clear bit is LOW
        }
    }
    // Port B
    else if( pin>=D8 && pin<=D13 ) {
        if( value == HIGH ) {
            MY_PORTB |= (1 << bit_per_port);  // set bit is HIGH
        }
        else{
            MY_PORTB &= ~(1 << bit_per_port);  // clear bit is LOW
        }
    }
    // Port C
    else if( pin>=A0 && pin<=A5 ) {
        if( value == HIGH ) {
            MY_PORTC |= (1 << bit_per_port);  // set bit is HIGH
        }
        else{
            MY_PORTC &= ~(1 << bit_per_port);  // clear bit is LOW
        }
    }
}


unsigned char digitalRead( unsigned char pin ) {
    unsigned char bit_per_port = uno_r3_pin_num2bit(pin);
    // Port D
    if( pin>=D0 && pin<=D7 ) {
        return (MY_PIND & (1 << bit_per_port)) != 0;
    }
    // Port B
    else if( pin>=D8 && pin<=D13 ) {
        return (MY_PINB & (1 << bit_per_port)) != 0;
    }
    // Port C
    // NOT BUG: A0 - A5 can be used as digital I/O
    else if( pin>=A0 && pin<=A5 ) {
        return (MY_PINC & (1 << bit_per_port)) != 0;
    }
    return 0;
}



/*
* ADCSRA(The ADC Control and Status Register A)
* BIT  7       6       5       4       3       2       1       0
* R/W  ADEN    ADSC    ADATE   ADIF    ADIE    ADPS2   ADPS1   ADPS0
*   ADPS<2:0>(3) ADC, prescaler
*     000: Division Factor 2 (Default)
*     001: Division Factor 2
*     010: Division Factor 4
*        :
*     111: Division Factor 128 <-- 16MHz / 128 = 125kHz
*   ADIE<3> Interrupt enable
*     0: Disable (Default)
*     1: Enable
*   ADIF<4> Interrupt flag
*     0: Complete conversion (Default)
*     1: Complete conversion
*   ADATE Auto trigger enable
*     0: Disable (Default)
*     1: Enable
*   ADSC<6> <- Start conversion
*     0: No effect (Default)
*     1: Start conversion
*   ADEN<7> <- Enable ADC
*     0: Disable (Default)
*     1: Enable
*
* ADCSRB(The ADC Control and Status Register B)
* BIT  7       6       5       4       3       2       1       0
* R/W  -       ACME    -       -       -       -       ADTS2   ADTS1
*   ADTS<2:0>(3) <- Auto trigger source
*   ACME<6> <- Analog Comparator Multiplexer Enable
*
* ADMUX(The ADC Multiplexer Selection Register)
* BIT  7       6       5       4       3       2       1       0
* R/W  REFS1   REFS0   ADLAR   MUX4    MUX3    MUX2    MUX1    MUX0
*   MUX<3:0>(4)
*     0000: ADC0 (Default) <-- A0 as input channel
*     0001: ADC1
*     0010: ADC2
*     0011: ADC3
*         :
*     1110: ADC14
*     1111: ADC15
*   ADLAR<5>
*     0: Right adjust result (Default)
*     1: Left adjust result
*   REFS<7:6>(2) <- AVCC as reference voltage
*     00: AREF, Internal Vref turned off (Default) <-- +5V as reference voltage
*     01: AVCC with external capacitor at AREF pin
*     10: Reserved
*     11: Internal 1.1V Voltage Reference with external capacitor at AREF pin
*
* ADCW(The ADC Data Register) equal ADCH(0x78) + ADCL(0x79)
* ADCW is not an official register name.
* ADLAR = 0
* BIT  15      14      13      12      11      10      9       8        <-- ADCH(0x78)
* R/W  -       -       -       -       -       -       ADC9    ADC8
* BIT  7       6       5       4       3       2       1       0        <-- ADCL(0x79)
* R/W  ADCH7   ADCH6   ADCH5   ADCH4   ADCH3   ADCH2   ADCH1   ADCH0
* ADLAR = 1
* BIT  15      14      13      12      11      10      9       8        <-- ADCH(0x78)
* R/W  ADCH7   ADCH6   ADCH5   ADCH4   ADCH3   ADCH2   ADCH1   ADCH0
* BIT  7       6       5       4       3       2       1       0        <-- ADCL(0x79)
* R/W  ADC9    ADC8    -       -       -       -       -       -
*/
#define VCC         5.0         // VCC: +5.0V
#define ADC_10BIT   1024.0      // 10bit ADC: 2^10 = 1024 

int analogRead( unsigned char pin ) {
    unsigned char bit_per_port = uno_r3_pin_num2bit(pin);
    // Port C
    if( pin>=A0 && pin<=A5 ) {
        // Initialize ADC
        MY_ADMUX = (MY_ADMUX & 0b11110000) | bit_per_port;  // pin as input channel
        MY_ADMUX &= ~(1 << BIT5);   // 0: Right adjust result
        MY_ADMUX |= (1 << BIT6);    // 10: AVCC as reference voltage
        MY_ADMUX &= ~(1 << BIT7);
//        MY_ADMUX = 0b01000000;  // AVCC as reference voltage, ADC0 as input channel
        MY_ADCSRA |= (1 << BIT7);   // 1: Enable ADC
        MY_ADCSRA |= (1 << BIT2);   // 111: prescaler = 128
        MY_ADCSRA |= (1 << BIT1);
        MY_ADCSRA |= (1 << BIT0);
//        MY_ADCSRA = 0b10000111;   // Enable ADC, prescaler = 128

        // Start ADC conversion
        MY_ADCSRA |= (1 << BIT6);
        // Wait for conversion to complete
        while (MY_ADCSRA & (1 << BIT6));
        // Get ADC value
        return MY_ADCW;
    }
    return 0;
}


/*
* Interrut Vectors for ATmega328P
*   0x000 RESET External Pin, Power-on Reset, Brown-out Reset and Watchdog System Reset
*   0x002 INT0 External Interrupt Request 0
*   0x004 INT1 External Interrupt Request 1
*   0x006 PCINT0 Pin Change Interrupt Request 0
*   0x008 PCINT1 Pin Change Interrupt Request 1
*   0x00A PCINT2 Pin Change Interrupt Request 2
*   0x00C WDT Watchdog Time-out Interrupt
*   0x00E TIMER2_COMPA Timer/Counter2 Compare Match A
*   0x010 TIMER2_COMPB Timer/Counter2 Compare Match B
*   0x012 TIMER2_OVF Timer/Counter2 Overflow
*   0x014 TIMER1_CAPT Timer/Counter1 Capture Event
*   0x016 TIMER1_COMPA Timer/Counter1 Compare Match A
*   0x018 TIMER1_COMPB Timer/Counter1 Compare Match B
*   0x01A TIMER1_OVF Timer/Counter1 Overflow
*   0x01C TIMER0_COMPA TimerCounter0 Compare Match A
*   0x01E TIMER0_COMPB TimerCounter0 Compare Match B
*   0x020 TIMER0_OVF Timer/Counter0 Overflow
*   0x022 SPI, STC SPI Serial Transfer Complete
*   0x024 USART, RX USART Rx Complete
*   0x026 USART, UDRE USART, Data Register Empty
*   0x028 USART, TX USART, Tx Complete
*   0x02A ADC ADC Conversion Complete
*   0x02C EE READY EEPROM Ready
*   0x02E ANALOG COMP Analog Comparator
*   0x030 TWI 2-wire Serial Interface
*   0x032 SPM READY Store Program Memory Ready
*
* PCICR(The Pin Change Interrupt Control Register) for ATmega328P
* BIT  7       6       5       4       3       2       1       0

* EICRA(The External Interrupt Control Register A)
* BIT  7       6       5       4       3       2       1       0
* R/W  -       -       -       -       ISC11   ISC10   ISC01   ISC00
*   ISCn<1:0>(2) <- Interrupt sense control of INT0 and INT1
*     INTn generates asynchronously an interrupt request
*     when the ISCn bits are set according to the table below
*     00: The low level of INTn         LEVEL
*     01: Any logical change on INTn    CHANGE
*     10: The falling edge of INTn      FALLING
*     11: The rising edge of INTn       RISING
*
* EICRB(The External Interrupt Control Register B)
* BIT  7       6       5       4       3       2       1       0
* R/W  ISC71   ISC70   ISC61   ISC60   ISC51   ISC50   ISC41   ISC40
*
* EIMSK(The External Interrupt Mask Register)
* BIT  7       6       5       4       3       2       1       0
* R/W  -       -       -       -       -       -       INT1    INT0
*   INTn(1) <- External Interrupt Request n Enable
*     0: Disable
*     1: Enable

* EIFR(The External Interrupt Flag Register)
* BIT  7       6       5       4       3       2       1       0
* R/W  -       -       -       -       -       -       INTF1   INTF0
*   INTFn(1) <- External Interrupt Flag n
*     0: No interrupt request
*     1: Interrupt request occurred
*     Write 1 to clear the flag
*
*/


/*
* TCCR1A(The Timer/Counter1 Control Register A)
* BIT  7       6       5       4       3       2       1       0
* R/W  COM1A1  COM1A0  COM1B1  COM1B0  -       -       WGM11   WGM10
*   COM1A<1:0>(2) <- Compare Output Mode for Channel A
*     00: Normal port operation, OC1A disconnected
*     01: Toggle OC1A on Compare Match
*     10: Clear OC1A on Compare Match
*     11: Set OC1A on Compare Match
*   COM1B<1:0>(2) <- Compare Output Mode for Channel B
*     00: Normal port operation, OC1B disconnected
*     01: Toggle OC1B on Compare Match
*     10: Clear OC1B on Compare Match
*     11: Set OC1B on Compare Match
*   WGM1<3:0>(4) <- Waveform Generation Mode
*     0000: Normal
*     0001: PWM, Phase Correct, 8-bit
*     0010: PWM, Phase Correct, 9-bit
*     0011: PWM, Phase Correct, 10-bit
*     0100: CTC, TOP = OCR1A
*     0101: Fast PWM, 8-bit, TOP = 0xFF
*     0110: Fast PWM, 9-bit, TOP = 0x1FF
*     0111: Fast PWM, 10-bit, TOP = 0x3FF
*     1000: PWM, Phase and Frequency Correct, TOP = ICR1
*     1001: PWM, Phase and Frequency Correct, TOP = OCR1A
*     1010: PWM, Phase Correct, TOP = ICR1
*     1011: PWM, Phase Correct, TOP = OCR1A
*     1100: CTC, TOP = ICR1
*     1101: Reserved
*     1110: Fast PWM, TOP = ICR1
*     1111: Fast PWM, TOP = OCR1A
*
* TCCR1B(The Timer/Counter1 Control Register B)
* BIT  7       6       5       4       3       2       1       0
* R/W  ICNC1   ICES1   -       WGM13   WGM12   CS12    CS11    CS10
*   ICNC1<7> <- Input Capture Noise Canceler
*     0: Disable
*     1: Enable
*   ICES1<6> <- Input Capture Edge Select
*     0: Falling edge
*     1: Rising edge
*   WGM1<3:0>(4) <- Waveform Generation Mode
*     0000: Normal
*     0001: PWM, Phase Correct, 8-bit
*     0010: PWM, Phase Correct, 9-bit
*     0011: PWM, Phase Correct, 10-bit
*     0100: CTC, TOP = OCR1A
*     0101: Fast PWM, 8-bit, TOP = 0xFF
*     0110: Fast PWM, 9-bit, TOP = 0x1FF
*     0111: Fast PWM, 10-bit, TOP = 0x3FF
*     1000: PWM, Phase and Frequency Correct, TOP = ICR1
*     1001: PWM, Phase and Frequency Correct, TOP = OCR1A
*     1010: PWM, Phase Correct, TOP = ICR1
*     1011: PWM, Phase Correct, TOP = OCR1A
*     1100: CTC, TOP = ICR1
*     1101: Reserved
*     1110: Fast PWM, TOP = ICR1
*     1111: Fast PWM, TOP = OCR1A
*   CS1<2:0>(3) <- Clock Select
*     000: No clock source (Timer/Counter stopped)
*     001: clkI/O/1 (No prescaling)
*     010: clkI/O/8 (From prescaler)
*     011: clkI/O/64 (From prescaler)
*     100: clkI/O/256 (From prescaler)
*     101: clkI/O/1024 (From prescaler)
*     110: External clock source on T1 pin, Clock on falling edge
*     111: External clock source on T1 pin, Clock on rising edge
*
* OCR1A(The Output Compare Register A)
* BIT  15      14      13      12      11      10      9       8
* R/W  -       -       -       -       -       -       OCR1A9  OCR1A8
* BIT  7       6       5       4       3       2       1       0
* R/W  OCR1A7  OCR1A6  OCR1A5  OCR1A4  OCR1A3  OCR1A2  OCR1A1  OCR1A0
*
* TIMSK1(The Timer/Counter1 Interrupt Mask Register)
* BIT  7       6       5       4       3       2       1       0
* R/W  -       -       -       -       -       ICIE1   -       TOIE1
*   ICIE1<5> <- Input Capture Interrupt Enable
*     0: Disable
*     1: Enable
*   TOIE1<0> <- Timer/Counter1, Overflow Interrupt Enable
*     0: Disable
*     1: Enable
*
* TIFR1(The Timer/Counter1 Interrupt Flag Register)
* BIT  7       6       5       4       3       2       1       0
* R/W  -       -       -       -       -       ICF1    -       TOV1
*   ICF1<5> <- Input Capture Flag 1
*     0: No input capture
*     1: Input capture occurred
*     Write 1 to clear the flag
*   TOV1<0> <- Timer/Counter1, Overflow Flag
*     0: No timer/counter overflow
*     1: Timer/counter overflow occurred
*     Write 1 to clear the flag
*/



void delay( unsigned long ms ) {
    while( ms-- ) {
        _delay_ms(1);
    }
}


// Digital I/O pin assign
#define LED_BUILTIN     D13     // on the board
#define LED             D13     // on the breadboard
#define BUZZER          D12     // on the breadboard
#define BUTTON          D2      // on the breadboard
#define VR              A0      // on the breadboard


// #############################################################################
// Arduino IDE
//    [File] - [Examples] - [03.Analog] - [AnalogInput]
// #############################################################################
/*
  Analog Input

  Demonstrates analog input by reading an analog sensor on analog pin 0 and
  turning on and off a light emitting diode(LED) connected to digital pin 13.
  The amount of time the LED will be on and off depends on the value obtained
  by analogRead().

  The circuit:
  - potentiometer
    center pin of the potentiometer to the analog input 0
    one side pin (either one) to ground
    the other side pin to +5V
  - LED
    anode (long leg) attached to digital output 13 through 220 ohm resistor
    cathode (short leg) attached to ground

  - Note: because most Arduinos have a built-in LED attached to pin 13 on the
    board, the LED is optional.

  created by David Cuartielles
  modified 30 Aug 2011
  By Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogInput
*/

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = D13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  // turn the ledPin on
  digitalWrite(ledPin, HIGH);
  // stop the program for <sensorValue> milliseconds:
  delay(sensorValue);
  // turn the ledPin off:
  digitalWrite(ledPin, LOW);
  // stop the program for for <sensorValue> milliseconds:
  delay(sensorValue);
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
