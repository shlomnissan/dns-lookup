// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_NET_UTILITIES_H
#define DNS_LOOKUP_NET_UTILITIES_H

#include <string_view>

namespace Network {
    using std::string_view;

    auto is_valid_ip_address(const string_view& address) -> bool;
}; // namespace Network

#endif // DNS_LOOKUP_NET_UTILITIES_H
