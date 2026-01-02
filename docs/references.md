# 参考文献・技術資料

本プロジェクトで参考にした論文、技術資料、データシートをまとめています。

---

## 目次

1. [脈波伝播速度（PWV）と血管評価](#脈波伝播速度pwvと血管評価)
2. [脈波到達時間（PAT）と血圧推定](#脈波到達時間patと血圧推定)
3. [光学式血流測定](#光学式血流測定)
4. [センサー技術](#センサー技術)
5. [データシート](#データシート)
6. [その他の技術資料](#その他の技術資料)

---

## 脈波伝播速度（PWV）と血管評価

### 主要論文

#### 1. Pulse transit time estimation of aortic pulse wave velocity and blood pressure using machine learning and simulated training data

**著者**: Janne M J Huttunen, Leo Kärkkäinen, Harri Lindholm  
**掲載誌**: PLoS Computational Biology, 2019  
**URL**: https://pmc.ncbi.nlm.nih.gov/articles/PMC6711549/  
**DOI**: 10.1371/journal.pcbi.1007259

**概要**:
- 心血管モデリングを用いた仮想被験者データベースの生成
- 機械学習（ガウス過程回帰）による大動脈PWV、血圧、一回拍出量の推定
- 光電式PPG信号から導出された脈波通過時間を使用
- 大動脈PWVの推定精度: r > 0.9（左頸動脈測定時）

**本プロジェクトへの示唆**:
- 複数部位での脈波測定から機械学習でPWVを高精度推定可能
- 足から足への脈波通過時間とピーク位置の組み合わせが有効

---

#### 2. Pulse transit time estimation of aortic pulse wave velocity

**著者**: 複数著者  
**掲載誌**: PMC6711549  
**URL**: https://pmc.ncbi.nlm.nih.gov/articles/PMC6711549/

**概要**:
- PWVの計算式: PWV = 距離（m） / 伝播時間（s）
- 2つの異なる動脈部位での脈波到達時間測定が基本
- 血管硬化度の評価に有効

**本プロジェクトへの示唆**:
- 複数部位測定の理論的基礎
- PWV計算の標準的な方法

---

#### 3. Assessment of Arterial Distensibility by Automatic Pulse Wave Velocity Measurement

**著者**: 複数著者  
**掲載誌**: Hypertension  
**URL**: https://www.ahajournals.org/doi/10.1161/01.HYP.26.3.485

**概要**:
- PWVは血管壁の伸展性と逆相関
- 自動PWV測定による動脈コンプライアンス評価
- Bramwell-Hill方程式: cPWV = 1/√(ρ × DC)

**本プロジェクトへの示唆**:
- PWVから血管コンプライアンス（弾性）を定量化可能
- 血管硬化度の客観的評価指標

---

#### 4. 新しい動脈硬化指標としての血圧脈波検査

**著者**: 松井芳夫  
**掲載誌**: 日本医療機器学会誌, 2010  
**URL**: https://www.jstage.jst.go.jp/article/jjmi/80/4/80_4_343/_pdf/-char/en

**概要**:
- 若年者のPWV: 約15 m/s
- 高齢者のPWV: 25 m/s以上（血管硬化）
- 2点間の距離と時間差からPWVを算出

**本プロジェクトへの示唆**:
- PWVの年齢別基準値
- 血管硬化度の判定基準

---

#### 5. 高血圧動脈弾性功能無創性評価（中国語）

**著者**: 複数著者  
**URL**: http://zhgxyzz.xml-journal.net/cn/article/pdf/preview/10.16439/j.cnki.1673-7245.2002.06.001.pdf

**概要**:
- 非侵襲的な動脈弾性機能評価
- 脈波伝播時間と血管内血流速度の関係
- 動脈可拡張性の定量的指標

**本プロジェクトへの示唆**:
- 非侵襲的測定の実用性
- 血管弾性の多角的評価

---

## 脈波到達時間（PAT）と血圧推定

### 主要論文

#### 6. Pulse Arrival Time as a Surrogate of Blood Pressure

**著者**: 複数著者  
**掲載誌**: Nature Scientific Reports, 2021  
**URL**: https://www.nature.com/articles/s41598-021-01358-4

**概要**:
- PATは血圧の代替指標として有用
- 圧力波の速度は多くのパラメータに依存
- 層流血流モデルでの良好な性能

**本プロジェクトへの示唆**:
- PATから血圧を推定可能
- 複数部位測定での血圧分布推定

---

#### 7. Pulse Arrival Velocity for Tracking Exercise-Induced Blood Pressure Changes

**著者**: LE Ryan et al.  
**掲載誌**: ScienceDirect, 2025  
**URL**: https://www.sciencedirect.com/science/article/pii/S1443950625016555

**概要**:
- 新しい指標PAV（Pulse Arrival Velocity）の提案
- PAV = L/PAT（距離/脈波到達時間）
- 運動誘発性血圧変化の追跡に有効

**本プロジェクトへの示唆**:
- PAVという新しい指標の可能性
- 動的な血圧変化の追跡

---

#### 8. Measuring Multi-Site Pulse Transit Time with an AI-Enabled System

**著者**: 複数著者  
**掲載誌**: arXiv, 2025  
**URL**: https://arxiv.org/html/2510.18141v1

**概要**:
- AI対応システムによる複数部位PTT測定
- 非接触測定の可能性
- 心血管疾患の事前スクリーニングへの応用

**本プロジェクトへの示唆**:
- 複数部位測定の重要性
- AI/機械学習の活用可能性

---

#### 9. Evaluation of the Linear Relationship Between Pulse Arrival Time and Blood Pressure

**著者**: B Escobar-Restrepo et al.  
**掲載誌**: Frontiers in Physiology, 2018  
**URL**: https://www.frontiersin.org/journals/physiology/articles/10.3389/fphys.2018.01848/full

**概要**:
- PATと血圧の線形関係の評価
- ECGから侵襲的血圧測定までのPAT測定
- 線形関係の程度を実証

**本プロジェクトへの示唆**:
- PATと血圧の関係性の理解
- 測定精度の向上

---

## 光学式血流測定

### 主要論文

#### 10. Transmissive-Detected Laser Speckle Contrast Imaging for Blood Flow Monitoring

**著者**: 複数著者  
**掲載誌**: Nature Light: Science & Applications, 2021  
**URL**: https://www.nature.com/articles/s41377-021-00682-8  
**DOI**: 10.1038/s41377-021-00682-8

**概要**:
- レーザースペックルコントラスト画像法（LSCI）
- 透過検出型LSCIによる血流モニタリング
- 時間分解能: ミリ秒オーダー
- 空間分解能: マイクロメートルオーダー

**本プロジェクトへの示唆**:
- 光学式血流測定の高度な手法
- 血流速度の直接測定の可能性
- 将来的な拡張オプション

---

#### 11. Photoplethysmography (PPG) Signal Processing and Analysis

**著者**: 複数著者  
**概要**:
- 光電式PPGの基本原理
- 信号処理とノイズ除去
- 脈拍検出アルゴリズム

**本プロジェクトへの示唆**:
- 光学式センサーの信号処理方法
- PPGの限界と課題の理解

---

## センサー技術

### 技術資料

#### 12. MEMS Microphone Technology Overview

**概要**:
- MEMSマイクの動作原理
- 周波数特性と感度
- ノイズ特性

**本プロジェクトへの示唆**:
- マイク方式の技術的基礎
- 心音測定への応用

---

#### 13. Force Sensitive Resistor (FSR) Technology

**概要**:
- ピエゾ抵抗式力センサーの原理
- 非線形特性と補正方法
- 応答速度と精度

**本プロジェクトへの示唆**:
- 圧力センサー方式の技術的基礎
- キャリブレーション方法

---

#### 14. Optical Heart Rate Sensor Design

**概要**:
- 光学式心拍センサーの設計
- LED波長の選択
- フォトダイオードの配置

**本プロジェクトへの示唆**:
- 光学式センサーの実装方法
- 測定精度の向上

---

## データシート

### センサー関連

#### 15. SPM0404HE5H-T MEMS Microphone Datasheet

**製造元**: Knowles  
**URL**: （秋月電子通商で入手可能）

**主要仕様**:
- 周波数帯域: 100 Hz ～ 10 kHz
- 感度: -42 dBV/Pa
- 供給電圧: 1.5 V ～ 3.6 V

---

#### 16. FSR402 Force Sensitive Resistor Datasheet

**製造元**: Interlink Electronics  
**URL**: （秋月電子通商で入手可能）

**主要仕様**:
- 測定範囲: 0～10 N
- 応答時間: < 1 ms
- 非線形特性あり

---

#### 17. Optical Pulse Sensor Module Datasheet

**URL**: https://akizukidenshi.com/catalog/g/g116107/

**主要仕様**:
- 赤外線LED（660 nm または 940 nm）
- フォトダイオード検出器
- 供給電圧: 3.3 V ～ 5 V

---

### マイコン関連

#### 18. ATSAMD21G18 Microcontroller Datasheet

**製造元**: Microchip  
**URL**: https://www.microchip.com/

**主要仕様**:
- ARM Cortex-M0+ 48 MHz
- ROM: 256 kB
- RAM: 32 kB
- GPIO: 11ピン

---

#### 19. Seeeduino XIAO Documentation

**製造元**: Seeed Studio  
**URL**: https://wiki.seeedstudio.com/Seeeduino-XIAO/

**概要**:
- ピン配置図
- Arduino IDE設定方法
- サンプルコード

---

## その他の技術資料

### 信号処理

#### 20. Digital Signal Processing for Biomedical Applications

**概要**:
- 生体信号のデジタルフィルタリング
- ノイズ除去技術
- ピーク検出アルゴリズム

**本プロジェクトへの示唆**:
- 脈波信号の前処理方法
- リアルタイム処理の実装

---

### 機械学習

#### 21. Machine Learning for Cardiovascular Signal Analysis

**概要**:
- 心血管信号の機械学習分析
- 特徴抽出
- 分類・回帰モデル

**本プロジェクトへの示唆**:
- PWV推定の高度化
- 異常検出アルゴリズム

---

### 医療機器設計

#### 22. Medical Device Design Guidelines

**概要**:
- 医療機器の安全基準
- 生体適合性
- 電磁両立性（EMC）

**本プロジェクトへの示唆**:
- 安全性の確保
- 将来的な製品化への準備

---

## 関連ウェブサイト

### 学術データベース

- **PubMed Central**: https://www.ncbi.nlm.nih.gov/pmc/
- **IEEE Xplore**: https://ieeexplore.ieee.org/
- **Nature**: https://www.nature.com/
- **Frontiers**: https://www.frontiersin.org/

### 技術コミュニティ

- **Arduino Forum**: https://forum.arduino.cc/
- **Seeed Studio Wiki**: https://wiki.seeedstudio.com/
- **GitHub**: https://github.com/

### 部品調達

- **秋月電子通商**: https://akizukidenshi.com/
- **Digi-Key**: https://www.digikey.jp/
- **Mouser**: https://www.mouser.jp/

---

## 引用形式

本プロジェクトの論文や資料を引用する際は、以下の形式を使用してください。

### APA形式

```
Huttunen, J. M. J., Kärkkäinen, L., & Lindholm, H. (2019). Pulse transit time estimation of aortic pulse wave velocity and blood pressure using machine learning and simulated training data. PLoS Computational Biology, 15(8), e1007259. https://doi.org/10.1371/journal.pcbi.1007259
```

### IEEE形式

```
J. M. J. Huttunen, L. Kärkkäinen, and H. Lindholm, "Pulse transit time estimation of aortic pulse wave velocity and blood pressure using machine learning and simulated training data," PLoS Comput. Biol., vol. 15, no. 8, p. e1007259, Aug. 2019, doi: 10.1371/journal.pcbi.1007259.
```

---

## 更新履歴

- 2026-01-02: 初版作成、主要論文22件を追加

---

## 貢献

新しい参考文献や技術資料を見つけた場合は、Pull Requestで追加してください。

## ライセンス

本リファレンスリストはMITライセンスの下で公開されています。ただし、各論文や資料は元の著作権者に帰属します。
