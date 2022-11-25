// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "common/buffer.h"
#include "common/exception.h"

namespace Common {
   void Buffer::write(const char* bytes, uint16_t len) {
        if (size + len > max_size) {
            throw BufferOutOfRange();
        }
        std::copy(bytes, bytes + len, buffer.data() + size);
        size += len;
    } 
}


