void setup() {
  // ボーレート:9600bps, データ長:8bit, パリティ:無し, ストップビット:1bit
  Serial.begin(9600, SERIAL_8N1);
  // ボード上に実装済みのLEDを出力に設定 ※LED_BUILTINは13と同値
  pinMode(LED_BUILTIN, OUTPUT);
}


// カウンタをクリア
int counter = 0;

void loop() {
  // カウンタ値を送信
  Serial.write(counter);

  // LEDを点灯
  digitalWrite(LED_BUILTIN, HIGH);
  // 100msスリープ
  delay(100);
  // LEDを消灯
  digitalWrite(LED_BUILTIN, LOW);
  // 100msスリープ
  delay(900);
  // カウンタをインクリメント
  counter++;
}
