# Project1_MAX30101: M5AtomS3による血流計測

## 概要

このプロジェクトでは、M5AtomS3マイクロコントローラーとSparkFun社のSEN-16474（MAX30101搭載）光検出器ブレークアウトボードを使用して、血流の変動を計測します。センサーから取得した赤色光および赤外線光の反射データをシリアル通信経由でPCに出力し、グラフ化することを目的とします。

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

**注意:** SparkFunのブレークアウトボードはQwiicコネクタを搭載していますが、M5AtomS3のGroveポートとは互換性がありません。接続には注意してください。

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
5.  センサーに指を置くと、赤色光と赤外線光のデータがグラフとして表示されます。

## 注意事項

- このプロジェクトで得られるデータは、医療目的の診断や生命維持のためには使用できません。あくまで教育およびデモンストレーション目的のものです。

## 参考資料

1.  [M5Stack Docs - AtomS3][2]
2.  [SparkFun Photodetector (MAX30101) Hookup Guide][3]
3.  [MAX30101 Datasheet][4]

[1]: https://docs.m5stack.com/en/arduino/atomS3
[2]: https://docs.m5stack.com/en/core/AtomS3
[3]: https://learn.sparkfun.com/tutorials/sparkfun-photodetector-max30101-hookup-guide/all
[4]: https://cdn.sparkfun.com/assets/8/1/c/9/0/MAX30101_Datasheet.pdf
