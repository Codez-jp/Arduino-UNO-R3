// Servo Arduino UNO R3 sample code
// for ELEGOO UNO R3 Project Complete Starter Kit
// based on ELEGOO original version

// The circuit:
//   - Servo signal(S) pin to Arduino D9(9) pin
//   - Servo VCC(+5V) pin to Arduino 5V(5V) pin
//   - Servo GND(GND) pin to Arduino GND(GND) pin

// Define Arduino UNO R3 pins
// port D
#define D0  0
#define D1  1
#define D2  2
#define D3  3
#define D4  4
#define D5  5
#define D6  6
#define D7  7
// port B
#define D8  8
#define D9  9
#define D10 10
#define D11 11
#define D12 12
#define D13 13
// port C
#define A0  14
#define A1  15
#define A2  16
#define A3  17
#define A4  18
#define A5  19

// include the Servo library
#include <Servo.h>

// create Servo object
Servo servo;

// variable to store the servo position
int servo_pos = 0;

// Define Servo pin
const int SERVO_PIN = D9;


void setup() {
    // attaches the servo on pin 9 to the servo object
    servo.attach( SERVO_PIN );
    // baud rate: 9600bps, data length: 8bit, parity:none, stop bit: 1bit
    Serial.begin( 9600, SERIAL_8N1 );
}


void loop() {
    // goes from 0 degrees to 180 degrees
    for( servo_pos = 0; servo_pos <= 180; servo_pos += 1 ){
        // in steps of 1 degree
        // tell servo to go to position in variable 'servo_pos'
        servo.write( servo_pos );              
        // wait for 15 ms to reach the position
        delay( 15 );
    }
    // goes from 180 degrees to 0 degrees
    for( servo_pos = 180; servo_pos >= 0; servo_pos -= 1 ){
        // tell servo to go to position in variable 'servo_pos'
        servo.write( servo_pos );
        // wait for 15 ms to reach the position
        delay( 15 );
    }
}
