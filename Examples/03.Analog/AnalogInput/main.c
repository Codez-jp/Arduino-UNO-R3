// #include "avr/io.h"
#define F_CPU 16000000UL
#include "util/delay.h"  // _delay_ms()

#define MY_DDRB     (*(volatile unsigned char *)(0x24))
#define MY_PORTB    (*(volatile unsigned char *)(0x25))

#define MY_ADCW     (*(volatile unsigned short *)(0x78))
#define MY_ADCSRA   (*(volatile unsigned char *)(0x7a))
#define MY_ADMUX    (*(volatile unsigned char *)(0x7c))


#define D13     5  // Port-B bit6
#define MY_ADSC 6


void init_adc( void ) {
    // MUX<3:0>(4)
    // ADLAR<5>
    // REFS<7:6>(2) <- AVCC as reference voltage
    MY_ADMUX = 0b01000000; // AVCC as reference voltage, ADC0 as input channel
    // ADPS<2:0>(3) <- ADC, prescaler
    // ADIE<3>
    // ADIF<4>
    // ADATE<5>
    // ADSC<6>
    // ADEN<7> <- Enable ADC
    MY_ADCSRA = 0b10000111; // Enable ADC, prescaler = 128
}


uint16_t read_adc( void ) {
    MY_ADCSRA |= (1 << MY_ADSC); // Start conversion
    while ( MY_ADCSRA & (1 << MY_ADSC) ); // Wait for conversion to complete
    return MY_ADCW; // Return result
}


int main( void ) {
    init_adc();
    MY_DDRB |= (1 << D13); // Set PB5 as output

    while( 1 ) {
        uint16_t adc_value = read_adc();
        if( adc_value > 512 ) {
            MY_PORTB |= (1 << D13); // Turn on LED
        } else {
            MY_PORTB &= ~(1 << D13); // Turn off LED
        }
        _delay_ms( 100 );
    }
}
