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

    size_t println(const __FlashStringHelper* s);
    size_t println(const String& s);
    size_t println(const char c[]);
    size_t println(char c);
    size_t println(unsigned char c, int base = DEC);
    size_t println(int i, int base = DEC);
    size_t println(unsigned int i, int base = DEC);
    size_t println(long l, int base = DEC);
    size_t println(unsigned long l, int base = DEC);
    size_t println(long long l, int base = DEC);
    size_t println(unsigned long long l, int base = DEC);
    size_t println(double d, int digits = 2);
    size_t println(const Printable& x);
    size_t println(struct tm* timeinfo, const char* format = NULL);

  protected:
    void handleWebPage(AsyncWebServerRequest* request);
    void handleWSEvent(AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, void* arg, uint8_t* data, size_t len);

  protected:
    AsyncWebServer* _server;
    AsyncWebSocket* _ws;
    MessageHandler  _msg_handler;
};

extern WebSerialClass WebSerial;