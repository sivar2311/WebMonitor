#include <Arduino.h>

#include <WebSerial.h>
#include <WiFi.h>

const char* wifi_ssid = "your_wifi_ssid";
const char* wifi_pass = "your_wifi_pass";

AsyncWebServer server(80);

void setup() {
    Serial.begin(115200);
    Serial.print("Connecting WiFi");
    WiFi.begin(wifi_ssid, wifi_pass);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.println("connected.");

    WebSerial.begin(&server);
    server.begin();

    Serial.printf("Open your browser and navigate to http://%s/webserial\r\n", WiFi.localIP().toString().c_str());
}

void loop() {
    WebSerial.printf("uptime: %d\r\n", millis() / 1000);
    delay(1000);
}