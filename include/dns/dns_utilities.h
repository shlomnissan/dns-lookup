// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_DNS_UTILITIES_H
#define DNS_LOOKUP_DNS_UTILITIES_H

#include <fstream>
#include <sstream>
#include <string>
#include <string_view>

namespace Dns {
    static constexpr char default_dns[] = "8.8.8.8";

    std::string get_dns_server();
    std::string_view type_to_string(uint16_t type);
}

#endif  // DNS_LOOKUP_DNS_UTILITIES_H
