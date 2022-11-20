// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_SOCKET_H
#define DNS_LOOKUP_SOCKET_H

#include "endpoint.h"

namespace network {
    class Socket {
    public:
        explicit Socket(const Endpoint& endpoint);

        // Delete copy constructor and assignment operator.
        Socket(const Socket&) = delete;
        Socket& operator=(const Socket&) = delete;

        ~Socket();

    private:
        int fd_socket {};
    };
};

#endif  // DNS_LOOKUP_SOCKET_H
