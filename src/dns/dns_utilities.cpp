// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "dns/dns_utilities.h"
#include "dns/types.h"
#include "network/net_utilities.h"

namespace Dns {
    std::string get_dns_server() {
        std::ifstream file;
        file.open("/etc/resolv.conf");
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                if (line.find("nameserver") == 0) {
                    std::string address = line.substr(11);
                    if (Network::is_valid_ip_address(address)) {
                        return address;
                    }
                }
            }
        }
        return default_dns;
    }

    std::string_view type_to_string(uint16_t type) {
        if (type == TYPE_A) return "A";
        if (type == TYPE_NS) return "NS";
        if (type == TYPE_CNAME) return "CNAME";
        if (type == TYPE_MX) return "MX";
        if (type == TYPE_TXT) return "TXT";
        if (type == TYPE_AAAA) return "AAAA";
        if (type == TYPE_ANY) return "ANY";
        return "UNDEFINED";
    }

    std::string_view rcode_to_string(uint8_t rcode) {
        if (rcode == RCODE_NOERROR) return "NOERROR";
        if (rcode == RCODE_FORMERR) return "FORMERR";
        if (rcode == RCODE_SERVFAIL) return "SERVFAIL";
        if (rcode == RCODE_NXDOMAIN) return "NXDOMAIN";
        if (rcode == RCODE_NOTIMP) return "NOTIMP";
        if (rcode == RCODE_REFUSED) return "REFUSED";
        return "UNDEFINED";
    }
} // namespace Dns