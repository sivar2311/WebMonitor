#pragma once

#include <ESPAsyncWebServer.h>
#include <Print.h>

class WebSerialClass : public Print {
  public:
    WebSerialClass();
    void begin(AsyncWebServer* server, const char* url = "/webserial");
    virtual size_t write(uint8_t data) override;
    virtual size_t write(const uint8_t* buffer, size_t len) override;
  protected:
    void handleWebPage(AsyncWebServerRequest* request);
    AsyncWebServer* _server;
    AsyncWebSocket* _ws;
};

extern WebSerialClass WebSerial;