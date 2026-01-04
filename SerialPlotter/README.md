# SerialPlotter

## 概要

`SerialPlotter` は、USB-Serial経由でデバイスから受信した単一列の数値データをリアルタイムで時系列グラフにプロットするWindowsアプリケーションです。Arduinoのシリアルプロッターのように、簡単な操作でデータの可視化が可能です。

## 主な機能

-   利用可能なCOMポートの自動検出と選択
-   主要なボーレートの選択
-   リアルタイムでのデータプロット
-   プロットのクリア機能
-   接続/切断の簡単な切り替え

## 使い方

1.  `SerialPlotter/bin/Release/net8.0-windows/` フォルダにある `SerialPlotter.exe` を実行します。
2.  アプリケーションが起動したら、ドロップダウンリストからデバイスが接続されているCOMポートを選択します。
3.  デバイスのボーレートに合わせてボーレートを選択します。
4.  「接続」ボタンをクリックすると、データの受信とプロットが開始されます。
5.  データは1行ごとに1つの数値を送信してください（改行コード `\n` が必要です）。
6.  「切断」ボタンでいつでも通信を停止できます。
7.  「クリア」ボタンでグラフを初期化できます。

## 開発環境

-   .NET 8.0
-   Windows Forms
-   ScottPlot (グラフ描画ライブラリ)
-   System.IO.Ports (シリアル通信)

## ビルド方法

1.  .NET 8.0 SDKをインストールします。
2.  リポジトリのルートで以下のコマンドを実行します。

    ```bash
    cd SerialPlotter/SerialPlotter
    dotnet build -c Release
    ```

3.  ビルドが成功すると、`SerialPlotter/SerialPlotter/bin/Release/net8.0-windows/` に実行ファイルが生成されます。
