#include "BufferedWebMonitor.h"

namespace WebMon {

size_t BufferedWebMonitor::write(uint8_t data) {
    return _buffer.write(data);
}

void BufferedWebMonitor::flush() {
    if (!_buffer.length()) return;
    WebMonitor.print(_buffer);
    _buffer.clear();
}

}  // namespace WebMon

WebMon::BufferedWebMonitor BufferedWebMonitor;