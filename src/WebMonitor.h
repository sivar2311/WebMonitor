#pragma once

#include <ESPAsyncWebServer.h>
#include <Print.h>

#include "StreamString.h"
#include "WebMonitorClient.h"

namespace WebMon {

class WebMonitorClient;

class WebMonitorClass : public Print {
  public:
    using MessageHandler = std::function<void(const String&, WebMonitorClient&)>;
    using ConnectHandler = std::function<void(WebMonitorClient&)>;

  public:
    WebMonitorClass();
    void begin(int port = 80, const char* url = "/webmonitor");
    void begin(AsyncWebServer* server, const char* url = "/webmonitor");
    void onMessage(MessageHandler msg_handler);
    void onConnect(ConnectHandler con_handler);

    virtual size_t write(uint8_t data) override;
    virtual size_t write(const uint8_t* buffer, size_t len) override;
    virtual int    availableForWrite() override;

    template <typename T>
    size_t println(T s) {
        StreamString buffer;
        buffer.println(s);
        return write((uint8_t*)buffer.c_str(), buffer.length());
    }

  protected:
    void handleWebPage(AsyncWebServerRequest* request);
    void handleWSEvent(AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, void* arg, uint8_t* data, size_t len);

  protected:
    AsyncWebServer* _server;
    AsyncWebSocket* _ws;
    MessageHandler  _msg_handler;
    ConnectHandler  _con_handler;
};

}  // namespace WebMon

extern WebMon::WebMonitorClass WebMonitor;
using WebMon::WebMonitorClient;