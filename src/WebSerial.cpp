#include "WebSerial.h"

#include "WebPage.h"

WebSerialClass::WebSerialClass()
    : _server(nullptr)
    , _ws(nullptr) {}

void WebSerialClass::begin(AsyncWebServer* server, const char* url) {
    if (_server) return;
    _server = server;
    _server->on(url, HTTP_GET, std::bind(&WebSerialClass::handleWebPage, this, std::placeholders::_1));
    _ws = new AsyncWebSocket("/webserialws");
    _ws->onEvent(std::bind(&WebSerialClass::handleWSEvent, this,
                           std::placeholders::_1,
                           std::placeholders::_2,
                           std::placeholders::_3,
                           std::placeholders::_4,
                           std::placeholders::_5,
                           std::placeholders::_6));
    _server->addHandler(_ws);
}

void  WebSerialClass::onMessage(MessageHandler msg_handler) {
    _msg_handler = msg_handler;
}

void WebSerialClass::handleWebPage(AsyncWebServerRequest* request) {
    request->send(200, "text/html", (const char*) webPage);
}

void WebSerialClass::handleWSEvent(AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, void* arg, uint8_t* data, size_t len) {
    if (type == WS_EVT_DATA && data && len && _msg_handler) {
        char buf[len+1];
        buf[len] = 0;
        memcpy(buf, data, len);
        _msg_handler(buf);
    }
}

size_t WebSerialClass::write(uint8_t data) {
    if (!_ws) return 0;
    _ws->textAll(&data, 1);
    return 1;
}

size_t WebSerialClass::write(const uint8_t* buffer, size_t len) {
    if (!_ws) return 0;
    _ws->textAll((const char*)buffer, len);
    return len;
}

WebSerialClass WebSerial;