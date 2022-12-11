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

        // TODO: check bounds
        auto seek(int value) { pos += value; }

        [[nodiscard]] auto getData() const { return buffer.data(); }
        [[nodiscard]] auto getCurrData() const { return buffer.data() + pos; }
        [[nodiscard]] auto getSize() const { return size; }

        template <typename T> auto read_bytes() -> T {
            if (std::is_same_v<T, uint32_t>) {
                uint32_t output = static_cast<T>(
                    (buffer[pos] << 24) + 
                    (buffer[pos + 1] << 16) +
                    (buffer[pos + 2] << 8) +
                    (buffer[pos + 3])
                );
                seek(sizeof(T));
                return output;
            }
            if (std::is_same_v<T, uint16_t>) {
                uint16_t output = static_cast<T>(
                    (buffer[pos] << 8) +
                    (buffer[pos + 1])
                );
                seek(sizeof(T));
                return output;
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