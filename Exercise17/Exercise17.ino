// ESP32 -> ThingSpeak (DHT11)
// Upload with Arduino IDE (Board: your ESP32)

// Libraries
#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

// ===== CONFIG =====
#define ssid       "Gække"
#define password   "fred249h"
const char* thingspeakWriteAPIKey = "SELF4806W72NNNF3";

#define DHTPIN 19        // data pin (change if needed)
#define DHTTYPE DHT11    // DHT 11

DHT dht(DHTPIN, DHTTYPE);

// ThingSpeak endpoint (HTTP)
const char* thingspeakServer = "http://api.thingspeak.com";

unsigned long lastSend = 0;
const unsigned long sendInterval = 20000UL; // 20 seconds (ThingSpeak friendly)

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println();
  Serial.println("ESP32 DHT11 -> ThingSpeak");

  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() - start > 20000) { // 20s timeout
      Serial.println();
      Serial.println("WiFi connection timeout — restarting...");
      ESP.restart();
    }
  }
  Serial.println();
  Serial.print("Connected, IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Read every sendInterval
  if (millis() - lastSend >= sendInterval) {
    lastSend = millis();
    sendSensorToThingSpeak();
  }
}

void sendSensorToThingSpeak() {
  // Read DHT (try a couple of times if fail)
  float temperature = NAN;
  float humidity = NAN;
  const int maxAttempts = 3;
  for (int attempt = 1; attempt <= maxAttempts; ++attempt) {
    humidity = dht.readHumidity();
    temperature = dht.readTemperature(); // Celsius
    if (!isnan(humidity) && !isnan(temperature)) break;
    Serial.printf("DHT read failed (attempt %d). Retrying...\n", attempt);
    delay(1000);
  }

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor after retries.");
    return;
  }

  Serial.printf("Temp: %.1f °C, Hum: %.1f %%\n", temperature, humidity);

  // Build ThingSpeak update URL:
  // Example: http://api.thingspeak.com/update?api_key=WRITEKEY&field1=23.4&field2=54.2
  String url = String(thingspeakServer) + "/update?api_key=" + thingspeakWriteAPIKey;
  url += "&field1=" + String(temperature, 1);
  url += "&field2=" + String(humidity, 1);

  // Send HTTP GET
  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();
  if (httpCode > 0) {
    String payload = http.getString();
    Serial.printf("ThingSpeak response code: %d, payload: %s\n", httpCode, payload.c_str());
    // ThingSpeak returns the entry ID (number) if success; <=0 if fail
  } else {
    Serial.printf("HTTP GET failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}