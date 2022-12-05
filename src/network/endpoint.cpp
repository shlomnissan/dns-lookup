// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "network/endpoint.h"

namespace Network {
    Endpoint::Endpoint(const std::string& host, const std::string& port) {
        addrinfo hints {};
        hints.ai_socktype = SOCK_DGRAM;
        if (getaddrinfo(host.c_str(), port.c_str(), &hints, &address)) {
            std::cerr << "getaddrinfo() failed. [" << errno << "]\n";
            exit(EXIT_FAILURE);
        }
    }

    Endpoint::~Endpoint() { freeaddrinfo(address); }
}; // namespace Network
