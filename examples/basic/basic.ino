#include <Arduino.h>
#include <WebMonitor.h>
#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

const char* wifi_ssid = "your_wifi_ssid";
const char* wifi_pass = "your_wifi_pass";

void setup() {
    Serial.begin(115200);
    Serial.print("Connecting WiFi");
    WiFi.begin(wifi_ssid, wifi_pass);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.println("connected.");

    WebMonitor.begin();

    Serial.printf("Open your webbrowser and navigate to http://%s/webmonitor\r\n", WiFi.localIP().toString().c_str());
}

void loop() {
    WebMonitor.printf("uptime: %d\r\n", millis() / 1000);
    Serial.printf("uptime: %d\r\n", millis() / 1000);
    delay(1000);
}
