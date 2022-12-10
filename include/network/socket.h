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
        Socket& operator=(const Socket&) = delete;

        ~Socket();

        [[nodiscard]] auto send(const Buffer& buffer) const -> bool;
        [[nodiscard]] auto receive() const -> Buffer;

    private:
        int fd_socket {};
        int address_len;
        sockaddr* address;
    };
}; // namespace Network

#endif // DNS_LOOKUP_SOCKET_H
