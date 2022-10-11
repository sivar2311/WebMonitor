#pragma once

#include "WebMonitor.h"

namespace WebMon {

class WebMonitorClient : public Print {
  public:
    virtual size_t write(uint8_t data) override;
    virtual size_t write(const uint8_t* data, size_t len) override;
    virtual int    availableForWrite() override;
    IPAddress      remoteIP();
    uint16_t       remotePort();
    virtual void   flush() override;

  protected:
    friend class WebMonitorClass;
    WebMonitorClient(AsyncWebSocketClient* client);
    AsyncWebSocketClient* _client;
    StreamString          _buffer;
};

}  // namespace WebMon