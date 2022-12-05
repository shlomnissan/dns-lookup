// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_BUFFER_H
#define DNS_LOOKUP_BUFFER_H

#include <array>
#include <cstdint>
#include <limits>

#include "common/exception.h"

namespace Common {
    class Buffer {
    public:
        static constexpr int max_size = std::numeric_limits<uint16_t>::max();

        Buffer() = default;

        Buffer(const char* bytes, unsigned long len) { write(bytes, len); }

        void write(const char* bytes, unsigned long len) {
            if (size + len > max_size) { throw BufferOutOfRange(); }
            std::copy(bytes, bytes + len, buffer.data() + size);
            size += len;
        }

        [[nodiscard]] const char* getData() const { return buffer.data(); }
        [[nodiscard]] uint16_t getSize() const { return size; }

    private:
        uint16_t size = 0;
        std::array<char, max_size> buffer;
    };
}; // namespace Common

#endif // DNS_LOOKUP_BUFFER_H