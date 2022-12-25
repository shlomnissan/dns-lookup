// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "network/endpoint.h"

namespace Network {
    Endpoint::Endpoint(const std::string& host, const std::string& port) {
        addrinfo hints {};
        hints.ai_socktype = SOCK_DGRAM;
        if (getaddrinfo(host.c_str(), port.c_str(), &hints, &address)) {
            throw InvalidAddress();
        }
    }

    Endpoint::Endpoint(Endpoint&& src) noexcept : address(src.address) {
        src.address = nullptr;
    }

    auto Endpoint::operator=(Endpoint&& rhs) noexcept -> Endpoint& {
        if (this != &rhs) {
            std::swap(address, rhs.address);
        }
        return *this;
    }

    Endpoint::~Endpoint() {
        if (address != nullptr) {
            freeaddrinfo(address);
        }
    }
}; // namespace Network
