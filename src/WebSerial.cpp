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
    _server->addHandler(_ws);
}

void WebSerialClass::handleWebPage(AsyncWebServerRequest* request) {
    request->send(200, "text/html", webPage);
}

size_t WebSerialClass::write(uint8_t data) {
    if (!_ws) return 0;
    _ws->textAll(&data, 1);
    return 1;
}

size_t WebSerialClass::write(const uint8_t* buffer, size_t len) {
    if (!_ws) return 0;
    _ws->textAll((const char*) buffer, len);
    return len;
}

WebSerialClass WebSerial;