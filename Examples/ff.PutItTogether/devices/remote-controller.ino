// Remote Controller Arduino UNO R3 sample code
// for ELEGOO UNO R3 Project Complete Starter Kit

// Define IR Receiver pin
const int RECV_PIN = 11;


void setup() {
    // Set IR Receiver pin to input mode
    pinMode( RECV_PIN, INPUT );
    // baud rate: 9600bps, data length: 8bit, parity:none, stop bit: 1bit
    Serial.begin( 9600, SERIAL_8N1 );
}


void loop() {
    // read IR Receiver if data is available
    if( Serial.available() ){
        int ir_val = Serial.read();
        Serial.print( "IR value: " );
        Serial.println( ir_val );
    }
}

