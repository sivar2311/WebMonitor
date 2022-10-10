#include "WebMonitor.h"

#include "WebPage.h"

namespace WebMon {

WebMonitorClient::WebMonitorClient(AsyncWebSocketClient* client)
    : _client(client) {}

size_t WebMonitorClient::write(uint8_t data) {
    if (!_client) return 0;
    _client->text(&data, 1);
    return 1;
}

size_t WebMonitorClient::write(const uint8_t* buffer, size_t len) {
    if (!_client) return 0;
    _client->text((const char*)buffer, len);
    return len;
}

int WebMonitorClient::availableForWrite() {
    return _client->canSend();
}

WebMonitorClass::WebMonitorClass()
    : _server(nullptr)
    , _ws(nullptr) {}

void WebMonitorClass::begin(int port, const char* url) {
    AsyncWebServer* server = new AsyncWebServer(port);
    server->begin();
    begin(server, url);
}

void WebMonitorClass::begin(AsyncWebServer* server, const char* url) {
    if (_server) return;
    _server = server;
    _server->on(url, HTTP_GET, std::bind(&WebMonitorClass::handleWebPage, this, std::placeholders::_1));
    _ws = new AsyncWebSocket("/wmws");
    _ws->onEvent(std::bind(&WebMonitorClass::handleWSEvent, this,
                           std::placeholders::_1,
                           std::placeholders::_2,
                           std::placeholders::_3,
                           std::placeholders::_4,
                           std::placeholders::_5,
                           std::placeholders::_6));
    _server->addHandler(_ws);
}

void WebMonitorClass::onMessage(MessageHandler msg_handler) {
    _msg_handler = msg_handler;
}

void WebMonitorClass::onConnect(ConnectHandler con_handler) {
    _con_handler = con_handler;
}

void WebMonitorClass::handleWebPage(AsyncWebServerRequest* request) {
    AsyncWebServerResponse* response = request->beginResponse_P(200, "text/html", webPage);
    request->send(response);
}

void WebMonitorClass::handleWSEvent(AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, void* arg, uint8_t* data, size_t len) {
    WebMonitorClient wm_client(client);

    if (type == WS_EVT_DATA && data && len && _msg_handler) {
        char buf[len + 1];
        buf[len] = 0;
        memcpy(buf, data, len);
        String message(buf);
        _msg_handler(message, wm_client);
    }

    if (type == WS_EVT_CONNECT && _con_handler) _con_handler(wm_client);
}

size_t WebMonitorClass::write(uint8_t data) {
    if (!_ws) return 0;
    _ws->textAll(&data, 1);
    return 1;
}

size_t WebMonitorClass::write(const uint8_t* buffer, size_t len) {
    if (!_ws) return 0;
    _ws->textAll((const char*)buffer, len);
    return len;
}

int WebMonitorClass::availableForWrite() {
    return _ws->availableForWriteAll();
}

}  // namespace WebMon

WebMon::WebMonitorClass WebMonitor;