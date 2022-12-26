// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_ENDPOINT_H
#define DNS_LOOKUP_ENDPOINT_H

#include <netdb.h>
#include <stdexcept>
#include <string>

namespace Network {
    class Endpoint {
    public:
        Endpoint(const std::string& host, const std::string& port);

        // Delete copy constructor and copy assignment operator.
        Endpoint(const Endpoint&) = delete;
        Endpoint& operator=(const Endpoint&) = delete;

        // Implements move constructor and move assignment operator.
        Endpoint(Endpoint&& src) noexcept;
        auto operator=(Endpoint&& rhs) noexcept -> Endpoint&;

        [[nodiscard]] auto getFamily() const { return address->ai_family; }
        [[nodiscard]] auto getSocketType() const { return address->ai_socktype; }
        [[nodiscard]] auto getProtocol() const { return address->ai_protocol; }
        [[nodiscard]] auto getAddress() const { return address->ai_addr; }
        [[nodiscard]] auto getAddressLength() const { return address->ai_addrlen; }

        ~Endpoint();

    private:
        addrinfo* address = nullptr;
    };

    struct InvalidAddress : public std::runtime_error {
        InvalidAddress() :
            std::runtime_error(
                "Failed to generate an address using getaddrinfo()."
            ) {}
    };
}; // namespace Network

#endif // DNS_LOOKUP_ENDPOINT_H
