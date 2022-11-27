// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_NET_UTILITIES_H
#define DNS_LOOKUP_NET_UTILITIES_H

#include <string_view>
#include <arpa/inet.h>
#include <array>

namespace Nnetwork {
    bool is_valid_ip_address(const std::string_view &address) {
        std::array<unsigned char, sizeof(struct in_addr)> buffer{};
        if (inet_pton(AF_INET, address.data(), buffer.data())) {
            return true;
        }
        return false;
    }
};

#endif  // DNS_LOOKUP_NET_UTILITIES_H
