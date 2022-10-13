#include "WebMonitorClient.h"

namespace WebMon {

WebMonitorClient::WebMonitorClient(AsyncWebSocketClient* client)
    : _client(client) {}

size_t WebMonitorClient::write(uint8_t data) {
    _buffer.print((char)data);
    yield();
    return 1;
}

size_t WebMonitorClient::write(const uint8_t* data, size_t len) {
    _buffer.write(data, len);
    return len;
}

int WebMonitorClient::availableForWrite() {
    return _buffer.availableForWrite();
}

IPAddress WebMonitorClient::remoteIP() {
    return _client->remoteIP();
}

uint16_t WebMonitorClient::remotePort() {
    return _client->remotePort();
}

void WebMonitorClient::flush()  {
    if (!_buffer.length()) return;
    _client->text(_buffer.c_str());
    _buffer.clear();
}

}  // namespace WebMon