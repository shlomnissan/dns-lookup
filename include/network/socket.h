// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_SOCKET_H
#define DNS_LOOKUP_SOCKET_H

#include "endpoint.h"
#include "common/buffer.h"

namespace Network {
    using namespace Common;

    class Socket {
    public:
        explicit Socket(const Endpoint& endpoint);

        // Delete copy constructor and assignment operator.
        Socket(const Socket&) = delete;
        Socket& operator=(const Socket&) = delete;

        ~Socket();

        [[nodiscard]] bool send(const Buffer& buffer) const;
        [[nodiscard]] Buffer receive() const;

    private:
        int fd_socket {};
        int address_len;
        sockaddr* address;
    };
};

#endif  // DNS_LOOKUP_SOCKET_H
