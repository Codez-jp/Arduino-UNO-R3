// https://www.instructables.com/I2C-between-Arduinos/
// I2C ライブラリをインクルードする
#include "Wire.h"

// 表示回数指示用カウンタをクリア
int disp_counter = 0;

void setup( ){
  // 基板上のLEDを出力に設定
  pinMode( LED_BUILTIN, OUTPUT );
  // スレーブモード（アドレス指定あり）で通信開始
  Wire.begin( 0x09 ); 
  // I2Cの受信割込み関数を登録
  Wire.onReceive( receiveEvent );
}
void receiveEvent( int bytes ){
  disp_counter = Wire.read( );  // I2Cの受信割込みが発生したら値を読み込む
}
void loop( ){
  // 受信した数字の回数LEDを点滅させる
  while( disp_counter > 0 ){
    digitalWrite( LED_BUILTIN, HIGH );
    delay( 200 );
    digitalWrite( LED_BUILTIN, LOW );
    delay( 200 );
    disp_counter--;
  }
}
