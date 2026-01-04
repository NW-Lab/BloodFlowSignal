/*
  Project1_MAX30101: M5AtomS3による血流計測（緑LEDのみ使用）
  
  このスケッチは、M5AtomS3とSparkFun SEN-16474 (MAX30101)を使用して、
  緑色LEDの反射データを取得し、シリアル経由でPCに出力します。
  緑LEDは皮膚表面の血流変化検出に最も感度が高く、心拍計測に適しています。
  
  接続:
  - M5AtomS3 G38 (SDA) -> MAX30101 SDA
  - M5AtomS3 G39 (SCL) -> MAX30101 SCL
  - M5AtomS3 3.3V -> MAX30101 3.3V (注: 緑LEDには5V推奨だが3.3Vでも動作)
  - M5AtomS3 GND -> MAX30101 GND
  
  必要なライブラリ:
  - M5Unified
  - SparkFun MAX3010x Pulse and Proximity Sensor Library
  
  使用方法:
  1. このコードをM5AtomS3に書き込む
  2. Arduino IDEのシリアルプロッタを開く (ツール > シリアルプロッタ)
  3. ボーレートを115200に設定
  4. センサーに指を置いてデータを確認
  
  外光ノイズ対策:
  - MAX30101内蔵のAmbient Light Cancellation (ALC)機能が自動的に動作
  - ALCはTrack/Holdサーキットで外光を自動キャンセル
  
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
  Serial.println("MAX30101 Blood Flow Measurement (Green LED Only)");
  Serial.println("================================================");
  
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
  
  // センサー設定（緑LEDのみ使用）
  // パラメータ: ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange
  byte ledBrightness = 0x3F;  // LED輝度 (0x00 - 0xFF) 緑LEDは高めに設定
  byte sampleAverage = 4;     // サンプル平均 (1, 2, 4, 8, 16, 32)
  byte ledMode = 3;           // LEDモード: 3 = 全LED使用可能（個別制御）
  int sampleRate = 100;       // サンプルレート (50, 100, 200, 400, 800, 1000, 1600, 3200)
  int pulseWidth = 411;       // パルス幅 (69, 118, 215, 411) マイクロ秒
  int adcRange = 4096;        // ADC範囲 (2048, 4096, 8192, 16384)
  
  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange);
  
  // 緑LEDのみを有効化（赤とIRを消灯）
  // これにより外光ノイズの影響を最小化し、緑LEDの高感度特性を活用
  particleSensor.setPulseAmplitudeRed(0);      // 赤LED OFF
  particleSensor.setPulseAmplitudeIR(0);       // IR LED OFF
  particleSensor.setPulseAmplitudeGreen(0x3F); // 緑LED ON (輝度: 0x3F)
  
  // Ambient Light Cancellation (ALC)は自動的に有効
  // ALCはMAX30101内部のTrack/Holdサーキットで外光を自動キャンセル
  
  Serial.println("Setup complete!");
  Serial.println("Configuration:");
  Serial.println("- LED Mode: Green only");
  Serial.println("- Sample Rate: 100 Hz");
  Serial.println("- Pulse Width: 411 us");
  Serial.println("- ADC Range: 4096");
  Serial.println("- Ambient Light Cancellation: Enabled (automatic)");
  Serial.println("");
  Serial.println("Place your finger on the sensor.");
  Serial.println("Green");  // シリアルプロッタ用のヘッダー
  
  // 初期化完了
  M5.Display.fillScreen(GREEN);
  M5.Display.setCursor(10, 50);
  M5.Display.println("Ready!");
  M5.Display.setCursor(10, 70);
  M5.Display.setTextSize(1);
  M5.Display.println("Green LED");
  
  delay(1000);
  M5.Display.fillScreen(BLACK);
}

void loop() {
  M5.update();  // M5AtomS3のボタン状態などを更新
  
  // センサーから緑色LEDのデータを取得
  long green = particleSensor.getGreen();
  
  // シリアルプロッタ用に出力
  Serial.println(green);
  
  // ディスプレイに簡易表示
  static unsigned long lastDisplayUpdate = 0;
  if (millis() - lastDisplayUpdate > 500) {  // 500msごとに更新
    lastDisplayUpdate = millis();
    
    M5.Display.fillScreen(BLACK);
    M5.Display.setTextSize(1);
    M5.Display.setCursor(5, 10);
    M5.Display.setTextColor(GREEN);
    M5.Display.println("Blood Flow");
    M5.Display.setTextColor(WHITE);
    
    M5.Display.setCursor(5, 30);
    M5.Display.print("Green: ");
    M5.Display.println(green);
    
    // 信号強度インジケーター
    // 緑LEDは赤やIRよりも反射が強いため、閾値を調整
    if (green > 80000) {
      M5.Display.setCursor(5, 50);
      M5.Display.setTextColor(GREEN);
      M5.Display.println("Excellent");
    } else if (green > 50000) {
      M5.Display.setCursor(5, 50);
      M5.Display.setTextColor(GREEN);
      M5.Display.println("Good Signal");
    } else if (green > 10000) {
      M5.Display.setCursor(5, 50);
      M5.Display.setTextColor(YELLOW);
      M5.Display.println("Weak Signal");
    } else {
      M5.Display.setCursor(5, 50);
      M5.Display.setTextColor(RED);
      M5.Display.println("No Signal");
    }
    
    // ALC状態表示
    M5.Display.setCursor(5, 70);
    M5.Display.setTextColor(CYAN);
    M5.Display.println("ALC: Active");
    
    M5.Display.setTextColor(WHITE);  // 色をリセット
  }
  
  // サンプリング間隔の調整 (約10ms = 100Hz)
  delay(10);
}
