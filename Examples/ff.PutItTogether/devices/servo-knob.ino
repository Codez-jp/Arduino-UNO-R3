// Servo Arduino UNO R3 sample code
// for ELEGOO UNO R3 Project Complete Starter Kit

// Include Servo library
#include <Servo.h>

// Create Servo object
Servo servo;

// Define Servo pin
const int SERVO_PIN = 9;

// Define Analog input pin
const int VR_PIN = 0;


void setup() {
    // Attach Servo object to Servo pin
    servo.attach( SERVO_PIN );
    // Set Servo initial position to 90 degrees
    servo.write( 90 );
    // Set Analog input pin to input mode
    pinMode( VR_PIN, INPUT );
    // baud rate: 9600bps, data length: 8bit, parity:none, stop bit: 1bit
    Serial.begin( 9600, SERIAL_8N1 );
}

void loop() {
    // Read Analog input pin
    int vr_val = analogRead( VR_PIN );
    // Map Analog input value to Servo angle
    int servo_angle = map( vr_val, 0, 1023, 0, 180 );
    // Apply VR value to Servo angle
    servo.write( servo_angle );
    // Print Servo angle
    Serial.println( servo_angle );
    // Wait for 100 ms
    delay( 100 );
}