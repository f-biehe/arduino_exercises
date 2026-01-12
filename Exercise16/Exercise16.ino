// Control an LED though webserver

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Gække";
const char* password = "fred249h";

WebServer server(80);

const int ledPin = 19;  // GPIO19
bool ledState = false;

void handleRoot() {
  String html = "<!DOCTYPE html><html><head><title>ESP32 LED Control</title></head><body>";
  html += "<h1>ESP32 LED Control</h1>";
  html += "<p>LED is currently: ";
  html += (ledState ? "ON" : "OFF");
  html += "</p>";
  html += "<form action=\"/toggle\" method=\"POST\"><button type=\"submit\">Toggle LED</button></form>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleToggle() {
  ledState = !ledState;
  digitalWrite(ledPin, ledState ? HIGH : LOW);
  server.sendHeader("Location", "/");
  server.send(303);  // Redirect back to root
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/toggle", HTTP_POST, handleToggle);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
