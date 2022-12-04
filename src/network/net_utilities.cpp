// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <arpa/inet.h>
#include <array>

#include "network/net_utilities.h"

namespace Network {
    bool is_valid_ip_address(const std::string_view &address) {
        std::array<unsigned char, sizeof(struct in_addr)> buffer{};
        if (inet_pton(AF_INET, address.data(), buffer.data())) {
            return true;
        }
        return false;
    }
};

