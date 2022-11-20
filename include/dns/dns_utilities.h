// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_DNS_UTILITIES_H
#define DNS_LOOKUP_DNS_UTILITIES_H

#include <fstream>
#include <sstream>
#include <string>
#include <string_view>

#include "network/net_utilities.h"

namespace dns {
    static constexpr char default_dns[] = "8.8.8.8";

    std::string get_dns_server() {
        std::ifstream file;
        file.open("/etc/resolv.conf");
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                if (line.find("nameserver") == 0) {
                    std::string address = line.substr(11);
                    if (network::is_valid_ip_address(address)) {
                        return address;
                    }
                }
            }
        }
        return default_dns;
    }
}

#endif  // DNS_LOOKUP_DNS_UTILITIES_H
