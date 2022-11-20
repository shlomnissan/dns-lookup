// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

#include "network/socket.h"

namespace network {
    Socket::Socket(const Endpoint &endpoint) {
        fd_socket = socket(
            endpoint.getFamily(),
            endpoint.getSocketType(),
            endpoint.getProtocol()
        );
        if (fd_socket < 0) {
            std::cerr << "socket() failed. [" << errno << "]\n";
            exit(EXIT_FAILURE);
        }
    }

    Socket::~Socket() {
        close(fd_socket);
    }
}