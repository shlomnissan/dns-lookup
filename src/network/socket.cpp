// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

#include "network/socket.h"

namespace Network {
    Socket::Socket(const Endpoint& endpoint)
        : address_len(endpoint.getAddressLength()), address(endpoint.getAddress()) {
        fd_socket = socket(
            endpoint.getFamily(), endpoint.getSocketType(), endpoint.getProtocol()
        );

        if (fd_socket < 0) { throw InvalidSocket(); }
    }

    Socket::Socket(Socket&& src) noexcept
        : fd_socket(src.fd_socket),
          address_len(src.address_len),
          address(src.address) {
        src.fd_socket = 0;
        src.address_len = 0;
        src.address = nullptr;
    }

    auto Socket::operator=(Socket&& rhs) noexcept -> Socket& {
        if (this != &rhs) {
            std::swap(fd_socket, rhs.fd_socket);
            std::swap(address_len, rhs.address_len);
            std::swap(address, rhs.address);
        }
        return *this;
    }

    auto Socket::send(const Buffer& buffer) const -> bool {
        auto bytes_sent = sendto(
            fd_socket, buffer.getData(), buffer.getSize(), 0, address, address_len
        );
        return bytes_sent == buffer.getSize();
    }

    auto Socket::receive() const -> Buffer {
        char buffer[Buffer::max_size];
        auto bytes_received =
            recvfrom(fd_socket, buffer, Buffer::max_size, 0, nullptr, nullptr);

        Buffer output;
        output.write(buffer, bytes_received);
        return output;
    }

    Socket::~Socket() {
        if (fd_socket != 0) {
            close(fd_socket);
        }
    }
} // namespace Network