// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "network/buffer.h"

namespace Network {
    auto Buffer::write(const char* bytes, unsigned long len) -> void {
        if (size + len > max_size) { throw BufferOutOfRange(); }
        std::copy(bytes, bytes + len, buffer.data() + size);
        size += len;
    }
} // namespace Network