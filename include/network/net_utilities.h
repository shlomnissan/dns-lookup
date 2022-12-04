// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_NET_UTILITIES_H
#define DNS_LOOKUP_NET_UTILITIES_H

#include <string_view>

namespace Network {
    bool is_valid_ip_address(const std::string_view &address);
};

#endif  // DNS_LOOKUP_NET_UTILITIES_H
