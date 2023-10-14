// https://www.instructables.com/I2C-between-Arduinos/
// I2C ライブラリをインクルードする
#include "Wire.h"

// 表示回数指示用カウンタをクリア
int disp_counter = 0;
void setup( ){
  // 基板上のLEDを出力に設定
  pinMode( LED_BUILTIN, OUTPUT );
  // マスターモード（アドレス無し）で通信開始
  Wire.begin( );
}
void loop( ){  
  Wire.beginTransmission( 0x09 );  // アドレスが0x09のスレーブデバイスと通信開始
  Wire.write( disp_counter );  // カウンタ値を送信
  Wire.endTransmission( );  // 通信終了
  // 動作確認用に3秒毎にLEDを点滅させる
  digitalWrite( LED_BUILTIN, HIGH );
  delay( 200 );
  digitalWrite( LED_BUILTIN, LOW );
  delay( 2800 );
  disp_counter++;  // カウンタをインクリメント
  if ( disp_counter > 5 ) disp_counter = 0;  // 6以上になったらカウンタをクリア
}
