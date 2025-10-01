/*
  Smart Farming (Wokwi Minimal, no MQTT)
  Sensors: DHT11 on GPIO4, Potentiometer -> GPIO34 (soil moisture)
  Alerts : LED (GPIO2) + Buzzer (GPIO27)
  Output : JSON lines to Serial for easy testing
  Sleep  : Optional short deep sleep for demo (disabled by default)

  Matches the core prototype in your report (ESP32 + DHT11 + soil moisture + alerts).
*/

#include <Arduino.h>
#include <DHT.h>

// ---------------- Pins ----------------
#define DHTPIN    4
#define DHTTYPE   DHT11
#define SOIL_ADC  34
#define LED_PIN    2     // On-board LED is OK in Wokwi
#define BUZZER    27

// ---------------- Thresholds ----------------
const float TEMP_HIGH_C  = 35.0;  // hot
const float HUM_LOW_PCT  = 30.0;  // dry air

// With Wokwi potentiometer: raw ≈ 0..4095 (0=wetter, 4095=drier).
// Calibrate these once you see raw values in Serial.
const int   SOIL_DRY_RAW = 3000;  // drier end
const int   SOIL_WET_RAW = 800;   // wetter end

// Optional: demo deep sleep (seconds). Keep 0 to disable in Wokwi.
#define SLEEP_SECONDS 0

DHT dht(DHTPIN, DHTTYPE);

// Map raw ADC to 0..100% moisture (100 = wet, 0 = dry)
int soilToPercent(int raw) {
  int lo = min(SOIL_DRY_RAW, SOIL_WET_RAW);
  int hi = max(SOIL_DRY_RAW, SOIL_WET_RAW);
  raw = constrain(raw, lo, hi);
  float span = (float)(SOIL_WET_RAW - SOIL_DRY_RAW);
  float pct  = 100.0f * (float)(SOIL_WET_RAW - raw) / span;
  pct = constrain(pct, 0.0f, 100.0f);
  return (int)roundf(pct);
}

void alertPattern(uint8_t times, int on_ms=120, int off_ms=120) {
  for (uint8_t i=0;i<times;i++) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER, HIGH);
    delay(on_ms);
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER, LOW);
    delay(off_ms);
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER, LOW);

  Serial.begin(115200);
  delay(100);
  dht.begin();

  alertPattern(1, 80, 80);  // power-on blink
}

void loop() {
  float t = dht.readTemperature(); // °C
  float h = dht.readHumidity();
  if (isnan(t) || isnan(h)) {
    Serial.println(F("{\"error\":\"DHT read failed\"}"));
    t = -1; h = -1;
  }

  int soilRaw  = analogRead(SOIL_ADC);
  int soilPct  = soilToPercent(soilRaw);

  // Alerts (visual/audio)
  bool any=false;
  if (soilPct < 35)      { any=true; alertPattern(3, 120, 140); }
  if (t > TEMP_HIGH_C)   { any=true; alertPattern(2, 200, 200); }
  if (h < HUM_LOW_PCT)   { any=true; alertPattern(1, 400, 200); }

  // JSON line for logging/plotting
  Serial.print("{\"temp_c\":");    Serial.print(t, 2);
  Serial.print(",\"humidity\":");  Serial.print(h, 2);
  Serial.print(",\"soil_pct\":");  Serial.print(soilPct);
  Serial.print(",\"soil_raw\":");  Serial.print(soilRaw);
  Serial.print(",\"alert\":");     Serial.print(any ? "true" : "false");
  Serial.println("}");

  if (SLEEP_SECONDS > 0) {
    Serial.printf("Sleeping %d sec...\n", SLEEP_SECONDS);
    delay(100);
    esp_sleep_enable_timer_wakeup((uint64_t)SLEEP_SECONDS * 1000000ULL);
    esp_deep_sleep_start();
  }

  delay(1000); // 1 Hz for sim
}