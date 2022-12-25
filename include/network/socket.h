// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_SOCKET_H
#define DNS_LOOKUP_SOCKET_H

#include "endpoint.h"
#include "network/buffer.h"

namespace Network {
    class Socket {
    public:
        explicit Socket(const Endpoint& endpoint);

        // Delete copy constructor and assignment operator.
        Socket(const Socket&) = delete;
        auto operator=(const Socket&) -> Socket& = delete;

        // Implements move constructor and move assignment operator.
        Socket(Socket&& src) noexcept;
        auto operator=(Socket&& rhs) noexcept -> Socket&;

        ~Socket();

        [[nodiscard]] auto send(const Buffer& buffer) const -> bool;
        [[nodiscard]] auto receive() const -> Buffer;

    private:
        int fd_socket = 0;
        int address_len = 0;
        sockaddr* address = nullptr;
    };

    struct InvalidSocket : public std::exception {
        const char* what() const throw() override {
            return "Failed to open socket using socket().";
        }
    };
}; // namespace Network

#endif // DNS_LOOKUP_SOCKET_H
