/*
  Project1_MAX30101: M5AtomS3による血流計測
  
  このスケッチは、M5AtomS3とSparkFun SEN-16474 (MAX30101)を使用して、
  赤色光と赤外線光の反射データを取得し、シリアル経由でPCに出力します。
  
  接続:
  - M5AtomS3 G38 (SDA) -> MAX30101 SDA
  - M5AtomS3 G39 (SCL) -> MAX30101 SCL
  - M5AtomS3 3.3V -> MAX30101 3.3V
  - M5AtomS3 GND -> MAX30101 GND
  
  必要なライブラリ:
  - M5Unified
  - SparkFun MAX3010x Pulse and Proximity Sensor Library
  
  使用方法:
  1. このコードをM5AtomS3に書き込む
  2. Arduino IDEのシリアルプロッタを開く (ツール > シリアルプロッタ)
  3. ボーレートを115200に設定
  4. センサーに指を置いてデータを確認
  
  注意: このコードは教育・デモ目的であり、医療診断には使用できません。
*/

#include <M5Unified.h>
#include <Wire.h>
#include "MAX30105.h"

MAX30105 particleSensor;

// I2Cピン定義 (M5AtomS3)
#define SDA_PIN 38
#define SCL_PIN 39

void setup() {
  // M5AtomS3初期化
  auto cfg = M5.config();
  M5.begin(cfg);
  
  // ディスプレイに初期化メッセージを表示
  M5.Display.setTextSize(1);
  M5.Display.setTextColor(WHITE);
  M5.Display.setCursor(10, 10);
  M5.Display.println("MAX30101");
  M5.Display.setCursor(10, 30);
  M5.Display.println("Init...");
  
  // シリアル通信開始
  Serial.begin(115200);
  Serial.println("MAX30101 Blood Flow Measurement");
  Serial.println("================================");
  
  // I2C初期化 (M5AtomS3のI2Cピンを指定)
  Wire.begin(SDA_PIN, SCL_PIN);
  
  // MAX30101センサー初期化
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("ERROR: MAX30101 was not found. Please check wiring/power.");
    M5.Display.fillScreen(RED);
    M5.Display.setCursor(10, 50);
    M5.Display.println("ERROR!");
    while (1);
  }
  
  Serial.println("MAX30101 detected!");
  
  // センサー設定
  // パラメータ: ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange
  byte ledBrightness = 0x1F;  // LED輝度 (0x00 - 0xFF)
  byte sampleAverage = 4;     // サンプル平均 (1, 2, 4, 8, 16, 32)
  byte ledMode = 2;           // LEDモード: 1=赤のみ, 2=赤+IR, 3=赤+IR+緑
  int sampleRate = 100;       // サンプルレート (50, 100, 200, 400, 800, 1000, 1600, 3200)
  int pulseWidth = 411;       // パルス幅 (69, 118, 215, 411) マイクロ秒
  int adcRange = 4096;        // ADC範囲 (2048, 4096, 8192, 16384)
  
  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange);
  
  // 初期化完了
  M5.Display.fillScreen(GREEN);
  M5.Display.setCursor(10, 50);
  M5.Display.println("Ready!");
  
  Serial.println("Setup complete!");
  Serial.println("Place your finger on the sensor.");
  Serial.println("Red,IR");  // シリアルプロッタ用のヘッダー
  
  delay(1000);
  M5.Display.fillScreen(BLACK);
}

void loop() {
  M5.update();  // M5AtomS3のボタン状態などを更新
  
  // センサーから赤色光と赤外線光のデータを取得
  long red = particleSensor.getRed();
  long ir = particleSensor.getIR();
  
  // シリアルプロッタ用にCSV形式で出力
  Serial.print(red);
  Serial.print(",");
  Serial.println(ir);
  
  // ディスプレイに簡易表示
  static unsigned long lastDisplayUpdate = 0;
  if (millis() - lastDisplayUpdate > 500) {  // 500msごとに更新
    lastDisplayUpdate = millis();
    
    M5.Display.fillScreen(BLACK);
    M5.Display.setTextSize(1);
    M5.Display.setCursor(5, 10);
    M5.Display.println("Blood Flow");
    
    M5.Display.setCursor(5, 30);
    M5.Display.print("Red: ");
    M5.Display.println(red);
    
    M5.Display.setCursor(5, 50);
    M5.Display.print("IR:  ");
    M5.Display.println(ir);
    
    // 信号強度インジケーター
    if (ir > 50000) {
      M5.Display.setCursor(5, 70);
      M5.Display.setTextColor(GREEN);
      M5.Display.println("Good Signal");
    } else if (ir > 10000) {
      M5.Display.setCursor(5, 70);
      M5.Display.setTextColor(YELLOW);
      M5.Display.println("Weak Signal");
    } else {
      M5.Display.setCursor(5, 70);
      M5.Display.setTextColor(RED);
      M5.Display.println("No Signal");
    }
    M5.Display.setTextColor(WHITE);  // 色をリセット
  }
  
  // サンプリング間隔の調整 (約10ms = 100Hz)
  delay(10);
}
