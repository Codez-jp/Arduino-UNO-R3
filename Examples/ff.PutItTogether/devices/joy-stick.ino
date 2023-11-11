// Joystick Arduino UNO R3 sample code
// for ELEGOO UNO R3 Project Complete Starter Kit

// The circuit:
//   - Joystick switch(SW) output pin to Arduino D2(2) pin
//   - Joystick X(VRx) output pin to Arduino A0(A0) pin
//   - Joystick Y(VRy) output pin to Arduino A1(A1) pin
//   - Joystick VCC(+5V) pin to Arduino 5V(5V) pin <== not 3.3V!!
//   - Joystick GND(GND) pin to Arduino GND(GND) pin

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

// Define Joystick pins
const int SW_PIN = D2;   // Digital pin connected to switch output
const int X_PIN = A0;    // Analog pin connected to X output
const int Y_PIN = A1;    // Analog pin connected to Y output


void setup() {
    // Set switch pin to input mode and enable pull-up resistor
    pinMode( SW_PIN, INPUT_PULLUP );
    // Set X, Y pin for Analog input mode
    pinMode( X_PIN, INPUT );
    pinMode( Y_PIN, INPUT );
    // Set built-in LED to output
    pinMode(LED_BUILTIN, OUTPUT);
    // baud rate: 9600bps, data length: 8bit, parity:none, stop bit: 1bit
    Serial.begin( 9600, SERIAL_8N1 );
}


void loop() {
    // Read switch
    int sw_val = digitalRead( SW_PIN );
    // Print switch status
    //   LOW: pressed <-- input pin is pulluped!!
    //   HIGH: released
    if (sw_val == LOW) {
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.println("Button pressed");
    } else {
        digitalWrite(LED_BUILTIN, LOW);
        Serial.println("Button released");
    }
    // Read X, Y position
    int x_val = analogRead(X_PIN);
    int y_val = analogRead(Y_PIN);
    // Print X, Y position
    Serial.print("X: ");
    Serial.print(x_val);
    Serial.print(" Y: ");
    Serial.println(y_val);
    // Wait 1000ms
    delay(1000);
}
