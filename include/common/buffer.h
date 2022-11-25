// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_BUFFER_H
#define DNS_LOOKUP_BUFFER_H

#include <array>
#include <limits>
#include <cstdint>

namespace Common {
    class Buffer {
    public:
        static constexpr int max_size = std::numeric_limits<uint16_t>::max();

        void write(const char* bytes, uint16_t len);
        [[nodiscard]] const unsigned char* getData() const { return buffer.data(); }
        [[nodiscard]] uint16_t getSize() const { return size; }

    private:
        uint16_t size = 0;
        std::array<uint8_t, max_size> buffer;
    }; 
};

#endif  // DNS_LOOKUP_BUFFER_H