// #include "avr/io.h"
#define F_CPU 16000000UL
#include "util/delay.h"  // _delay_ms()

#define MY_DDRB (*(volatile unsigned char *)(0x24))
#define MY_PORTB (*(volatile unsigned char *)(0x25))

#define MY_ADCW (*(volatile unsigned short *)(0x78))
#define MY_ADCSRA (*(volatile unsigned char *)(0x7a))
#define MY_ADMUX (*(volatile unsigned char *)(0x7c))

#define D13 5  // Port-B bit6
#define D12 4  // Port-B bit5
#define MY_ADSC 6
#define MY_LED D13
#define MY_BUZZER D12


uint16_t read_adc( unsigned int adsc_bit)
{
    MY_ADCSRA |= (1 << adsc_bit);  // Start conversion
    while (MY_ADCSRA & (1 << adsc_bit));  // Wait for conversion to complete
    return MY_ADCW;  // Return result
}


// https://stackoverflow.com/questions/30422367/how-to-fix-error-message-builtin-avr-delay-cycles-expects-a-compile-time-inte
void delay_ms( int ms )
{
    while (0 < ms)
    {  
        _delay_ms(1);
        --ms;
    }
}


void blink( int led_bit, int ms )
{
    MY_PORTB |= (1 << led_bit); // Turn on LED
    delay_ms( ms );  // wait for ms ms
    MY_PORTB &= ~(1 << led_bit); // Turn off LED
    delay_ms( ms );  // wait for ms ms
}


void setup( void )
{
    /*
    * Data sheet of ATmega328P
    * http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf
    */
    /*
    * ADMUX – ADC Multiplexer Selection Register
    * MUX<3:0>(4)
    * ADLAR<5>
    * REFS<7:6>(2)
    */
    MY_ADMUX = 0b01000000;  // AVCC as reference voltage, ADC0 as input channel
    /*
    * ADCSRA – ADC Control and Status Register A
    * ADPS<2:0>(3)
    * ADIE<3>
    * ADIF<4>
    * ADATE<5>
    * ADSC<6>
    * ADEN<7>
    */
    MY_ADCSRA = 0b10000111;  // Enable ADC, prescaler = 128

    MY_DDRB |= (1 << MY_LED); // Digital OUT
    MY_DDRB |= (1 << MY_BUZZER); // Digital OUT
}


int main( void )
{
    setup( );

    while( 1 )
    {
        blink( MY_LED, read_adc( MY_ADSC ) );
        blink( MY_BUZZER, read_adc( MY_ADSC ) );
    }
}
