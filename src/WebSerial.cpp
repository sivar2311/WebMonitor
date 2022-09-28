#include "WebSerial.h"

#include "StreamString.h"
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

int WebSerialClass::availableForWrite() {
    return _ws->availableForWriteAll();
}

size_t WebSerialClass::println(const __FlashStringHelper* s) {
    StreamString buffer;
    buffer.println(s);
    return write((uint8_t*)buffer.c_str(), buffer.length());
}

size_t WebSerialClass::println(const String& s) {
    StreamString buffer;
    buffer.println(s);
    return write((uint8_t*)buffer.c_str(), buffer.length());
}

size_t WebSerialClass::println(const char c[]) {
    StreamString buffer;
    buffer.println(c);
    return write((uint8_t*)buffer.c_str(), buffer.length());
}

size_t WebSerialClass::println(char c) {
    StreamString buffer;
    buffer.println(c);
    return write((uint8_t*)buffer.c_str(), buffer.length());
}

size_t WebSerialClass::println(unsigned char c, int base) {
    StreamString buffer;
    buffer.println(c, base);
    return write((uint8_t*)buffer.c_str(), buffer.length());
}

size_t WebSerialClass::println(int i, int base) {
    StreamString buffer;
    buffer.println(i, base);
    return write((uint8_t*)buffer.c_str(), buffer.length());
}

size_t WebSerialClass::println(unsigned int i, int base) {
    StreamString buffer;
    buffer.println(i, base);
    return write((uint8_t*)buffer.c_str(), buffer.length());
}

size_t WebSerialClass::println(long l, int base) {
    StreamString buffer;
    buffer.println(l, base);
    return write((uint8_t*)buffer.c_str(), buffer.length());
}

size_t WebSerialClass::println(unsigned long l, int base) {
    StreamString buffer;
    buffer.println(l, base);
    return write((uint8_t*)buffer.c_str(), buffer.length());
}

size_t WebSerialClass::println(long long l, int base) {
    StreamString buffer;
    buffer.println(l, base);
    return write((uint8_t*)buffer.c_str(), buffer.length());
}
size_t WebSerialClass::println(unsigned long long l, int base) {
    StreamString buffer;
    buffer.println(l, base);
    return write((uint8_t*)buffer.c_str(), buffer.length());
}
size_t WebSerialClass::println(double d, int digits) {
    StreamString buffer;
    buffer.println(d, digits);
    return write((uint8_t*)buffer.c_str(), buffer.length());
}

size_t WebSerialClass::println(const Printable& x) {
    StreamString buffer;
    x.printTo(buffer);
    return write((uint8_t*)buffer.c_str(), buffer.length());
}

size_t WebSerialClass::println(struct tm* timeinfo, const char* format) {
    StreamString buffer;
    buffer.println(timeinfo, format);
    return write((uint8_t*)buffer.c_str(), buffer.length());
}

WebSerialClass WebSerial;