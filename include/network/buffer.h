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
        auto seek(int value) -> void;

        [[nodiscard]] auto data() const { return buffer.data(); }
        [[nodiscard]] auto currData() const { return buffer.data() + pos; }
        [[nodiscard]] auto getSize() const { return size; }

        template <typename T> auto readBytes() -> T {
            if (std::is_same_v<T, uint8_t>) {
                uint8_t output = static_cast<T>(buffer[pos]);
                seek(sizeof(T));
                return output;
            }
            if (std::is_same_v<T, uint16_t>) {
                auto b0 = readBytes<uint8_t>();
                auto b1 = readBytes<uint8_t>();
                return (b0 << 8) + b1;
            }
            if (std::is_same_v<T, uint32_t>) {
                auto b0 = readBytes<uint8_t>();
                auto b1 = readBytes<uint8_t>();
                auto b2 = readBytes<uint8_t>();
                auto b3 = readBytes<uint8_t>();
                return (b0 << 24) + (b1 << 16) + (b2 << 8) + b3;
            }
        }

    private:
        int pos = 0;
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