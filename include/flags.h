// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gflags/gflags.h>
#include <iostream>
#include <string>
#include <unordered_set>

#include "network/net_utilities.h"

DEFINE_string(host, "", "The hostname that you wish to look up");
DEFINE_string(type, "A", "The query's record type. The default record type is an A record");
DEFINE_string(server, "", "The DNS server address. A default server would be used otherwise");

static bool validateHost(const char* flagname, const std::string& value) {
    return value.empty() ? false : true;
}
DEFINE_validator(host, &validateHost);

static bool validateType(const char* flagname, const std::string& value) {
    std::unordered_set<std::string> valid_values {
        "A", "NS", "CNAME", "MX", "TXT", "AAAA", "ANY"
    };
    auto uppercase_value = Network::to_uppercase(value);
    if (!valid_values.contains(uppercase_value)) {
        std::cout << "Support record types are A, NS, CNAME, MX, TXT, and ANY" << '\n';
        return false;
    }
    return true;
}
DEFINE_validator(type, &validateType);

static bool validateServer(const char* flagname, const std::string& value) {
    if (value.empty()) return true;
    return Network::is_valid_ip_address(value);
}
DEFINE_validator(server, &validateServer);