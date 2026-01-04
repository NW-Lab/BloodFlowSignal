# ICS-43434マイクとM5AtomS3の調査結果

## ICS-43434 MEMS マイクロフォン仕様

### 基本情報
- 製品: Adafruit I2S MEMS Microphone Breakout - ICS-43434
- 製品URL: https://www.adafruit.com/product/6049
- チップ: TDK ICS43434
- インターフェース: I2S (デジタル出力)

### 技術仕様
- 感度: −26 dB FS ±1dB
- SNR (High Performance Mode): 65 dBA
- SNR (Low Power Mode): 64 dBA
- 消費電流 (High Performance Mode): 490 µA
- 消費電流 (Low Power Mode): 230 µA
- Acoustic Overload Point (AOP): 120 dB SPL
- サンプルレート (High Performance Mode): 23 ~ 51.6 kHz
- サンプルレート (Low Power Mode): 6.25 ~ 18.75 kHz
- 周波数範囲: 50Hz - 15KHz (一般的なオーディオ記録に適している)
- ローパスフィルター: 24KHz以上をカット
- データ出力: 24ビット

### ピン配置
- Clock (SCK/BCK): I2Sクロック信号
- Data (SD): I2Sデータ出力
- Word Select (WS/LRCLK): 左右チャンネル選択
- Select (SEL): チャンネル選択 (GND=Left, VDD=Right)
- VIN: 電源入力 (1.6V - 3.6V)
- GND: グランド

### 重要な特徴
- モノラルマイク（ステレオには2個必要）
- ボトムポート（底面に音孔）
- 5Vロジックには非対応（3.3V専用）
- ESP32、RP2040、SAMD21/51などのI2S対応マイコンに最適

## M5AtomS3 仕様

### 基本情報
- 製品URL: https://docs.m5stack.com/en/core/AtomS3
- SoC: ESP32-S3FN8
- Flash: 8MB
- サイズ: 24.0 x 24.0 x 12.9mm

### 電源仕様
- 入力電源: 5V (USB Type-C)
- 出力電圧: 3.3V
- DC-DC: SY8089

### 利用可能なGPIOピン
- G5, G6, G7, G8, G38, G39 (底面に配置)

### I2C使用状況
- MPU6886 (IMU): I2C Address 0x68
  - SDA: GPIO38
  - SCL: GPIO39

### 内蔵ペリフェラル
- 0.85インチ LCD (SPI接続)
  - MOSI: G21
  - SCK: G17
  - CS: G15
  - RS: G33
  - RST: G34
  - LCD_BL: G16

### HY2.0-4Pポート
- GND: Black
- 5V: Red
- G2: Yellow
- G1: White

### I2S接続の推奨ピン
ESP32-S3はI2S0とI2S1の2つのI2Sペリフェラルを持つ。
利用可能なGPIOピン（G5, G6, G7, G8）をI2S接続に使用可能。

推奨配線:
- I2S SCK (Clock): GPIO5
- I2S WS (Word Select): GPIO6
- I2S SD (Data): GPIO7
- SEL: GND (Left channel) または 3.3V (Right channel)
- VIN: 3.3V
- GND: GND

## 血流計測への応用

### 測定原理
マイクロフォンを使用して血流音（血管の拍動音）を検出する。
- 皮膚表面に近い血管（手首、首など）の拍動音を検出
- 低周波成分（1-10Hz程度）に心拍情報が含まれる
- ICS-43434の周波数範囲は50Hz-15KHzなので、低周波の心拍音検出に適している

### データ処理
1. I2Sインターフェースで24ビットデジタルデータを取得
2. サンプリングレート: 16kHz または 44.1kHz
3. データをシリアル経由でPCに送信
4. Arduino IDEのシリアルプロッターでリアルタイム表示

## 参考資料
- ICS-43434 Datasheet: https://invensense.tdk.com/wp-content/uploads/2016/02/DS-000069-ICS-43434-v1.2.pdf
- Adafruit製品ガイド: https://learn.adafruit.com/adafruit-i2s-mems-microphone-breakout
- M5AtomS3 Arduino Library: https://github.com/m5stack/M5Unified
- ESP32-S3 I2S Documentation: https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/api-reference/peripherals/i2s.html
