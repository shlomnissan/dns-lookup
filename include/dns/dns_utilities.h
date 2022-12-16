// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_DNS_UTILITIES_H
#define DNS_LOOKUP_DNS_UTILITIES_H

#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>

namespace Dns {
    using std::string;
    using std::string_view;

    static constexpr char default_dns[] = "8.8.8.8";

    auto get_dns_server() -> string;
    auto type_to_str(uint16_t type) -> string;
    auto rcode_to_str(uint8_t rcode) -> string;
    auto opcode_to_str(uint8_t opcode) -> string;
} // namespace Dns

#endif // DNS_LOOKUP_DNS_UTILITIES_H
