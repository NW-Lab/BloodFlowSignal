# Project1_MAX30101: M5AtomS3による血流計測（緑LED版）

## 概要

このプロジェクトでは、M5AtomS3マイクロコントローラーとSparkFun社のSEN-16474（MAX30101搭載）光検出器ブレークアウトボードを使用して、血流の変動を計測します。センサーから取得した**緑色光**の反射データをシリアル通信経由でPCに出力し、グラフ化することを目的とします。

緑色LEDは皮膚表面の血流変化を検出するのに最も感度が高く、心拍数測定において高いSN比（信号対雑音比）が期待できます。

## 使用機材

| 役割 | 型番 | メーカー |
|---|---|---|
| マイクロコントローラー | M5AtomS3 | M5Stack |
| センサー | SEN-16474 (MAX30101) | SparkFun |

## 接続

M5AtomS3とMAX30101センサーはI2Cインターフェースで接続します。M5AtomS3のGroveポート（HY2.0-4P）はI2C通信に対応していないため、背面のピンヘッダを使用します。

| M5AtomS3 (背面ピン) | MAX30101 (ブレークアウト) |
|---|---|
| 3.3V | 3.3V |
| GND | GND |
| G39 (SCL) | SCL |
| G38 (SDA) | SDA |

**注意:** SparkFunのブレークアウトボードはQwiicコネクタを搭載していますが、M5AtomS3のGroveポートとは互換性がありません。接続には注意してください。また、緑LEDの性能を最大限に引き出すには、センサーのVLEDピンに5Vを供給することが推奨されていますが、3.3Vでも動作します。

## セットアップ

### 1. Arduino IDEの環境設定

Arduino IDEにESP32ボードマネージャをインストールし、M5Stackのボード定義を追加する必要があります。詳細はM5Stackの公式ドキュメントを参照してください。

- [M5Stack Arduino Quick Start][1]

### 2. 必要なライブラリのインストール

Arduino IDEのライブラリマネージャから、以下の2つのライブラリをインストールしてください。

- **SparkFun MAX3010x Pulse and Proximity Sensor Library**: MAX30101センサーを制御するためのライブラリです。
- **M5Unified**: M5Stack製品群を統一的に扱うためのライブラリです。

## 使用方法

1.  このディレクトリにある`Project1_MAX30101.ino`をArduino IDEで開きます。
2.  M5AtomS3をPCに接続し、ボードとシリアルポートを正しく設定します。
3.  コードをM5AtomS3に書き込みます。
4.  Arduino IDEのシリアルプロッタ（`ツール` > `シリアルプロッタ`）を開き、ボーレートを`115200`に設定します。
5.  センサーに指を置くと、緑色光のデータがグラフとして表示されます。

## 外光ノイズ対策

MAX30101は、**Ambient Light Cancellation (ALC)** という強力な外光ノイズ除去機能を内蔵しています。この機能は、センサー内部のTrack/Hold回路によって外光の影響を自動的に測定値から差し引くことで、ダイナミックレンジを向上させます。

Arduinoコードでは、`particleSensor.setup()`関数を呼び出すことでALC機能が**自動的に有効化**されます。特別な設定は不要です。

## 注意事項

- このプロジェクトで得られるデータは、医療目的の診断や生命維持のためには使用できません。あくまで教育およびデモンストレーション目的のものです。

## 参考資料

1.  [M5Stack Docs - AtomS3][2]
2.  [SparkFun Photodetector (MAX30101) Hookup Guide][3]
3.  [MAX30101 Datasheet][4]
4.  [How to select the green LED only on the MAX30101][5]

[1]: https://docs.m5stack.com/en/arduino/atomS3
[2]: https://docs.m5stack.com/en/core/AtomS3
[3]: https://learn.sparkfun.com/tutorials/sparkfun-photodetector-max30101-hookup-guide/all
[4]: https://www.analog.com/media/en/technical-documentation/data-sheets/max30101.pdf
[5]: https://ez.analog.com/optical_sensing/w/documents/20560/how-to-select-the-green-led-only-on-the-max30101
