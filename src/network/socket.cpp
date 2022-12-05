// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

#include "network/socket.h"

namespace Network {
    Socket::Socket(const Endpoint& endpoint)
        : address_len(endpoint.getAddressLength()),
          address(endpoint.getAddress()) {
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

    bool Socket::send(const Buffer& buffer) const {
        auto bytes_sent = sendto(
            fd_socket,
            buffer.getData(),
            buffer.getSize(),
            0,
            address,
            address_len
        );
        return bytes_sent == buffer.getSize();
    }

    Buffer Socket::receive() const {
        char buffer[Buffer::max_size];
        auto bytes_received =
            recvfrom(fd_socket, buffer, Buffer::max_size, 0, nullptr, nullptr);

        Buffer output;
        output.write(buffer, bytes_received);
        return output;
    }

    Socket::~Socket() { close(fd_socket); }
} // namespace Network