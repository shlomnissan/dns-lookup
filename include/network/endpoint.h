// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_ENDPOINT_H
#define DNS_LOOKUP_ENDPOINT_H

#include <iostream>
#include <netdb.h>
#include <string>

namespace Network {
    class Endpoint {
    public:
        Endpoint(const std::string& host, const std::string& port);

        // Delete copy constructor and assignment operator.
        Endpoint(const Endpoint&) = delete;
        Endpoint& operator=(const Endpoint&) = delete;

        [[nodiscard]] auto getFamily() const { return address->ai_family; }
        [[nodiscard]] auto getSocketType() const {
            return address->ai_socktype;
        }
        [[nodiscard]] auto getProtocol() const { return address->ai_protocol; }
        [[nodiscard]] auto getAddress() const { return address->ai_addr; }
        [[nodiscard]] auto getAddressLength() const {
            return address->ai_addrlen;
        }

        ~Endpoint();

    private:
        addrinfo* address {};
    };
}; // namespace Network

#endif // DNS_LOOKUP_ENDPOINT_H
