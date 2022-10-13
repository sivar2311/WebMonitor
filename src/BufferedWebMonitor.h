#pragma once

#include "WebMonitor.h"

namespace WebMon {

class BufferedWebMonitor : public Print {
  public:
    virtual size_t write(uint8_t) override;
    virtual size_t write(const uint8_t*, size_t) override;
    void flush();
  protected:
    StreamString _buffer;
};

}  // namespace WebMon

extern WebMon::BufferedWebMonitor BufferedWebMonitor;