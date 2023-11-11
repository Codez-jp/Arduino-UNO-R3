// Servo Arduino UNO R3 sample code
// for ELEGOO UNO R3 Project Complete Starter Kit
// based on ELEGOO original version

// include the Servo library
#include <Servo.h>

// create Servo object
Servo servo;
// variable to store the servo position
int servo_pos = 0;
// Define Servo pin
const int SERVO_PIN = 9;


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
