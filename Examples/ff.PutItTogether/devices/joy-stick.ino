// Joystick Arduino UNO R3 sample code
// for ELEGOO UNO R3 Project Complete Starter Kit

// Define Joystick pins
const int SW_PIN = 2;   // Digital pin connected to switch output
const int X_PIN = 0;    // Analog pin connected to X output
const int Y_PIN = 1;    // Analog pin connected to Y output


void setup() {
    // Set switch pin to input mode and enable pull-up resistor
    pinMode( SW_PIN, INPUT_PULLUP );
    digitalWrite( SW_PIN, HIGH );
    // Set X, Y pin for Analog input mode
    pinMode( X_PIN, INPUT );
    pinMode( Y_PIN, INPUT );
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
        Serial.println("Button pressed");
    } else {
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
}
