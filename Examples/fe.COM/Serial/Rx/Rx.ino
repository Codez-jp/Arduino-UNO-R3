void setup( ){
  Serial.begin( 9600 );
  pinMode( LED_BUILTIN, OUTPUT );
}

// 受信バイト数をクリア
int incomingByte = 0;

void loop() {
  // シリアルが有効な場合
  if( Serial.available( ) > 0 ){
    // データを１バイト読み込む
    incomingByte = Serial.read( );
    // 受信データを10進数で送信する
    Serial.print( "0d" );
    Serial.println( incomingByte, DEC );

    // LEDを点灯
    digitalWrite( LED_BUILTIN, HIGH );
    // 100ms点灯を保持
    delay( 100 );
    // LEDを消灯
    digitalWrite( LED_BUILTIN, LOW );
  }
}
