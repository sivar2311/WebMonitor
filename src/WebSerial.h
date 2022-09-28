#pragma once

#include <ESPAsyncWebServer.h>
#include <Print.h>

class WebSerialClass : public Print {
  public:
    using MessageHandler = std::function<void(const char*)>;

  public:
    WebSerialClass();
    void begin(AsyncWebServer* server, const char* url = "/webserial");
    void onMessage(MessageHandler msg_handler);

    virtual size_t write(uint8_t data) override;
    virtual size_t write(const uint8_t* buffer, size_t len) override;
    virtual int    availableForWrite() override;

  protected:
    void handleWebPage(AsyncWebServerRequest* request);
    void handleWSEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len);
    AsyncWebServer* _server;
    AsyncWebSocket* _ws;
    MessageHandler _msg_handler;
};

extern WebSerialClass WebSerial;