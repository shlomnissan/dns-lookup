// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_NET_UTILITIES_H
#define DNS_LOOKUP_NET_UTILITIES_H

#include <string>
#include <string_view>

namespace Network {
    auto is_valid_ip_address(std::string_view address) -> bool;
    auto to_uppercase(std::string_view source) -> std::string;
}; // namespace Network

#endif // DNS_LOOKUP_NET_UTILITIES_H
