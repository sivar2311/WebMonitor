#include "BufferedWebMonitor.h"

namespace WebMon {

size_t BufferedWebMonitor::write(uint8_t data) {
    _buffer.write(data);
    yield();
    return 1;
}
}

void BufferedWebMonitor::flush() {
    if (!_buffer.length()) return;
    WebMonitor.print(_buffer);
    _buffer.clear();
}

}  // namespace WebMon

WebMon::BufferedWebMonitor BufferedWebMonitor;