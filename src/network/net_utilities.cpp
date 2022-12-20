// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <algorithm>
#include <arpa/inet.h>
#include <array>

#include "network/net_utilities.h"

namespace Network {
    auto is_valid_ip_address(std::string_view address) -> bool {
        std::array<unsigned char, sizeof(struct in_addr)> buffer {};
        if (inet_pton(AF_INET, address.data(), buffer.data())) { return true; }
        return false;
    }

    auto to_uppercase(std::string_view source) -> std::string {
        std::string output {begin(source), end(source)};
        std::transform(begin(output), end(output), begin(output), ::toupper);
        return output;
    }
}; // namespace Network
