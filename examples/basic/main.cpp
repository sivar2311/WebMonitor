#include <Arduino.h>
#include <WebSerial.h>
#include <WiFi.h>

const char* wifi_ssid = "your_wifi_ssid";
const char* wifi_pass = "your_wifi_pass";
const int   port      = 80;
const char* url       = "/webserial";

AsyncWebServer server(port);

void setup() {
    Serial.begin(115200);
    Serial.print("Connecting WiFi");
    WiFi.begin(wifi_ssid, wifi_pass);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.println("connected.");

    WebSerial.begin(&server, url);
    server.begin();

    if (port == 80)
        Serial.printf("Open your webbrowser and navigate to http://%s%s\r\n", WiFi.localIP().toString().c_str(), url);
    else
        Serial.printf("Open your webbrowser and navigate to http://%s:%d%s\r\n", WiFi.localIP().toString().c_str(), port, url);
}

void loop() {
    WebSerial.printf("uptime: %d\r\n", millis() / 1000);
    Serial.printf("uptime: %d\r\n", millis() / 1000);
    delay(1000);
}