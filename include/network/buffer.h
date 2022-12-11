// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_BUFFER_H
#define DNS_LOOKUP_BUFFER_H

#include <array>
#include <cstdint>
#include <limits>

namespace Network {
    class Buffer {
    public:
        static constexpr int max_size = std::numeric_limits<uint16_t>::max();

        Buffer() = default;

        Buffer(const char* bytes, unsigned long len) { write(bytes, len); }

        auto write(const char* bytes, unsigned long len) -> void;

        [[nodiscard]] auto getData() const { return buffer.data(); }
        [[nodiscard]] auto getSize() const { return size; }

    private:
        uint16_t size = 0;
        std::array<char, max_size> buffer;
    };

    struct BufferOutOfRange : public std::exception {
        const char* what() const throw() override {
            return "The message buffer is out of range.";
        }
    };
}; // namespace Network

#endif // DNS_LOOKUP_BUFFER_H