/*
 * Project2: M5AtomS3とICS-43434マイクによる血流計測
 * 
 * このスケッチは、M5AtomS3とICS-43434 MEMSマイクを使用して
 * 血流音を計測し、シリアルプロッター経由でリアルタイムに可視化します。
 * 
 * ハードウェア接続:
 * - M5AtomS3 G5  -> ICS-43434 SCK
 * - M5AtomS3 G6  -> ICS-43434 WS
 * - M5AtomS3 G7  -> ICS-43434 SD
 * - M5AtomS3 3V3 -> ICS-43434 VIN
 * - M5AtomS3 GND -> ICS-43434 GND
 * - M5AtomS3 GND -> ICS-43434 SEL (Left channel)
 * 
 * 使用方法:
 * 1. Arduino IDEでこのスケッチをM5AtomS3に書き込む
 * 2. ツール -> シリアルプロッターを開く
 * 3. マイクを手首や首の動脈付近に配置する
 * 4. 波形を観察する
 */

#include <M5Unified.h>
#include <driver/i2s.h>

// I2S設定
#define I2S_PORT I2S_NUM_0
#define SAMPLE_RATE 16000           // サンプリングレート 16kHz
#define SAMPLE_BUFFER_SIZE 256      // バッファサイズ
#define BITS_PER_SAMPLE I2S_BITS_PER_SAMPLE_32BIT

// M5AtomS3のピン設定
#define I2S_MIC_SERIAL_CLOCK GPIO_NUM_5     // SCK (ビットクロック)
#define I2S_MIC_LEFT_RIGHT_CLOCK GPIO_NUM_6 // WS (ワードセレクト)
#define I2S_MIC_SERIAL_DATA GPIO_NUM_7      // SD (データ)

// I2S設定構造体
i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = BITS_PER_SAMPLE,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = 1024,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0
};

// I2Sピン設定構造体
i2s_pin_config_t i2s_mic_pins = {
    .bck_io_num = I2S_MIC_SERIAL_CLOCK,
    .ws_io_num = I2S_MIC_LEFT_RIGHT_CLOCK,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = I2S_MIC_SERIAL_DATA
};

// グローバル変数
int32_t raw_samples[SAMPLE_BUFFER_SIZE];
bool i2s_initialized = false;

void setup() {
    // M5Unifiedの初期化
    auto cfg = M5.config();
    M5.begin(cfg);
    
    // ディスプレイ初期化
    M5.Display.setRotation(0);
    M5.Display.setTextSize(1);
    M5.Display.fillScreen(BLACK);
    M5.Display.setCursor(0, 10);
    M5.Display.println("BloodFlow");
    M5.Display.println("Monitor");
    M5.Display.println("");
    M5.Display.println("ICS-43434");
    
    // シリアル通信の初期化
    Serial.begin(115200);
    while (!Serial) {
        delay(10);
    }
    
    delay(1000);
    
    // I2Sドライバのインストール
    esp_err_t err = i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
    if (err != ESP_OK) {
        Serial.printf("I2S driver install error: %d\n", err);
        M5.Display.fillScreen(RED);
        M5.Display.setCursor(0, 30);
        M5.Display.println("I2S Error!");
        while (1) {
            delay(1000);
        }
    }
    
    // I2Sピンの設定
    err = i2s_set_pin(I2S_PORT, &i2s_mic_pins);
    if (err != ESP_OK) {
        Serial.printf("I2S pin set error: %d\n", err);
        M5.Display.fillScreen(RED);
        M5.Display.setCursor(0, 30);
        M5.Display.println("Pin Error!");
        while (1) {
            delay(1000);
        }
    }
    
    i2s_initialized = true;
    
    // 初期化完了メッセージ
    Serial.println("# BloodFlow Monitor - ICS-43434");
    Serial.println("# Ready to measure...");
    
    M5.Display.fillScreen(GREEN);
    M5.Display.setCursor(0, 30);
    M5.Display.println("Ready!");
    
    delay(1000);
    M5.Display.fillScreen(BLACK);
}

void loop() {
    M5.update();
    
    if (!i2s_initialized) {
        return;
    }
    
    // I2Sデバイスからデータを読み取る
    size_t bytes_read = 0;
    esp_err_t result = i2s_read(
        I2S_PORT,
        raw_samples,
        sizeof(int32_t) * SAMPLE_BUFFER_SIZE,
        &bytes_read,
        portMAX_DELAY
    );
    
    if (result != ESP_OK) {
        Serial.println("# I2S read error");
        return;
    }
    
    int samples_read = bytes_read / sizeof(int32_t);
    
    // サンプルデータをシリアルプロッターに出力
    // 32ビットデータを右シフトして適切な範囲に正規化
    for (int i = 0; i < samples_read; i++) {
        // 上位24ビットを使用（ICS-43434は24ビット出力）
        int32_t sample = raw_samples[i] >> 8;
        Serial.println(sample);
    }
    
    // ボタンが押されたら情報を表示
    if (M5.BtnA.wasPressed()) {
        M5.Display.fillScreen(BLACK);
        M5.Display.setCursor(0, 10);
        M5.Display.printf("Rate:%dHz\n", SAMPLE_RATE);
        M5.Display.printf("Buf:%d\n", SAMPLE_BUFFER_SIZE);
        M5.Display.printf("Read:%d\n", samples_read);
        delay(2000);
        M5.Display.fillScreen(BLACK);
    }
}
