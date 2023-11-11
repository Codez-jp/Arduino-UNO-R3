// Ultra sonic sensor Arduino UNO R3 sample code
// for ELEGOO UNO R3 Project Complete Starter Kit

// The circuit:
//   - VCC pin to Arduino 5V(5V) pin
//   - Trig pin to Arduino D3(3) pin
//   - Echo pin to Arduino D2(2) pin
//   - GND pin to Arduino GND(GND) pin

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

// Define ultra sonic sensor pins
const int TRIG_PIN = D3;
const int ECHO_PIN = D2;

// Define ultra sonic sensor variables
long duration;
int distance;


void setup() {
    // initialize ultra sonic sensor pins
    pinMode( TRIG_PIN, OUTPUT );
    pinMode( ECHO_PIN, INPUT );
    // baud rate: 9600bps, data length: 8bit, parity:none, stop bit: 1bit
    Serial.begin( 9600, SERIAL_8N1 );
}


void loop() {
    // send a short pulse to trigger
    digitalWrite( TRIG_PIN, LOW );
    delayMicroseconds( 2 );
    digitalWrite( TRIG_PIN, HIGH );
    delayMicroseconds( 10 );
    digitalWrite( TRIG_PIN, LOW );
    // read the echo pin, which will be HIGH if the duration is greater than 38ms
    duration = pulseIn( ECHO_PIN, HIGH );
    // calculate the distance
    distance = duration * 0.034 / 2;
    // print out the distance
    Serial.print( "Distance: " );
    Serial.print( distance );
    Serial.println( " cm" );
    delay( 1000 );
}