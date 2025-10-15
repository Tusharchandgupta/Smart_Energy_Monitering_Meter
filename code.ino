#include <WiFi.h>
#include <PubSubClient.h>
#include <Arduino.h>
#include "ACS712.h"
#include <ZMPT101B.h>


// -------- Wi-Fi Credentials --------
const char* ssid = "TUSHAR-PC";
const char* password = "6307778096";

// -------- ThingsBoard MQTT Configuration --------
const char* mqttServer = "thingsboard.cloud";
const int mqttPort = 1883;
const char* accessToken = "u0robmwfchhfm9di5xay";  // Replace with your device access token

// -------- Sensor Pin Configuration --------
#define PIN_CURRENT 34
#define PIN_VOLTAGE 35

// -------- Sensor Objects --------
ACS712 ACS(PIN_CURRENT, 3.3, 4095, 100);       // ACS712, 100A variant
ZMPT101B voltageSensor(PIN_VOLTAGE, 50.0);    // initial sensitivity

// -------- Global Variables --------
WiFiClient wifiClient;
PubSubClient client(wifiClient);

float volt = 0.0;
float current = 0.0;
float power = 0.0;
float zeroOffset = 0.0;

// -------- Function Prototypes --------
void setup_wifi();
void reconnect();
void sendTelemetry();
void calibrateZeroCurrent();

// -------- Setup --------
void setup() {
  Serial.begin(115200);
  delay(100);

  setup_wifi();
  client.setServer(mqttServer, mqttPort);
  reconnect();

  // Sensor setup
  ACS.autoMidPoint();
  voltageSensor.setSensitivity(500.0f);
  calibrateZeroCurrent();

  Serial.println("🚀 Setup complete. Sending voltage/current/power data to ThingsBoard.");
}

// -------- Loop --------
void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  static unsigned long lastTelemetry = 0;
  if (millis() - lastTelemetry > 5000) {
    lastTelemetry = millis();
    sendTelemetry();
  }
}

// -------- Connect to Wi-Fi --------
void setup_wifi() {
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\n✅ Wi-Fi connected.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// -------- Reconnect to ThingsBoard MQTT --------
void reconnect() {
  while (!client.connected()) {
    Serial.print("🔄 Connecting to ThingsBoard... ");
    String clientId = "ESP32Client-" + String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), accessToken, "")) {
      Serial.println("✅ Connected to ThingsBoard.");
    } else {
      Serial.print("❌ Failed, rc=");
      Serial.print(client.state());
      Serial.println(" — retrying in 5 seconds.");
      delay(5000);
    }
  }
}

// -------- Send Telemetry to ThingsBoard --------
void sendTelemetry() {
  // ----- Read current -----
  float sum_mA = 0;
  const int samples = 100;
  for (int i = 0; i < samples; i++) {
    sum_mA += ACS.mA_AC();
  }
  float mA = sum_mA / samples;

  float corrected_mA = mA - zeroOffset;
  if (corrected_mA < 0) corrected_mA = 0;
  current = (corrected_mA > 15) ? corrected_mA / 1000.0 : 0.0;

  // ----- Read voltage -----
  float v = voltageSensor.getRmsVoltage();
  volt = (v > 50) ? v : 0.0;

  // ----- Calculate power -----
  power = volt * current;
  if (power < 1.0) power = 0.0;

  // ----- Prepare and send telemetry -----
  String payload = "{\"voltage\":" + String(volt, 2) +
                   ",\"current\":" + String(current, 3) +
                   ",\"power\":" + String(power, 2) + "}";

  client.publish("v1/devices/me/telemetry", payload.c_str());
  Serial.println("📡 Sent telemetry: " + payload);
}

// -------- Calibrate zero-current offset --------
void calibrateZeroCurrent() {
  Serial.println("Calibrating zero current... Ensure no load is connected!");
  float sum = 0;
  const int samples = 200;
  for (int i = 0; i < samples; i++) {
    sum += ACS.mA_AC();
    delay(5);
  }
  zeroOffset = sum / samples;
  Serial.print("Zero-current offset = "); Serial.println(zeroOffset, 3);
  Serial.println("Calibration done.");
}
