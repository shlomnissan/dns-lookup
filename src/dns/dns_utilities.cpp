// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <cstdint>
#include <random>

#include "dns/dns_utilities.h"
#include "dns/types.h"
#include "network/net_utilities.h"

namespace Dns {
    auto get_dns_server() -> string {
        std::ifstream file;
        file.open("/etc/resolv.conf");
        if (file.is_open()) {
            string line;
            while (std::getline(file, line)) {
                if (line.find("nameserver") == 0) {
                    string address = line.substr(11);
                    if (Network::is_valid_ip_address(address)) { return address; }
                }
            }
        }
        return default_dns;
    }

    auto generate_id() -> uint16_t {
        std::default_random_engine engine {(std::random_device())()};
        std::uniform_int_distribution<uint16_t> rand_dist {0x0000, 0xFFFF};
        return rand_dist(engine);
    }

    auto type_to_str(uint16_t type) -> string {
        if (type == TYPE_A) return "A";
        if (type == TYPE_NS) return "NS";
        if (type == TYPE_CNAME) return "CNAME";
        if (type == TYPE_SOA) return "SOA";
        if (type == TYPE_MX) return "MX";
        if (type == TYPE_TXT) return "TXT";
        if (type == TYPE_AAAA) return "AAAA";
        if (type == TYPE_ANY) return "ANY";
        return "N/A";
    }

    auto rcode_to_str(uint8_t rcode) -> string {
        if (rcode == RCODE_NOERROR) return "NOERROR";
        if (rcode == RCODE_FORMERR) return "FORMERR";
        if (rcode == RCODE_SERVFAIL) return "SERVFAIL";
        if (rcode == RCODE_NXDOMAIN) return "NXDOMAIN";
        if (rcode == RCODE_NOTIMP) return "NOTIMP";
        if (rcode == RCODE_REFUSED) return "REFUSED";
        return "N/A";
    }

    auto opcode_to_str(uint8_t opcode) -> string {
        if (opcode == OPCODE_QUERY) return "QUERY";
        if (opcode == OPCODE_IQUERY) return "IQUERY";
        if (opcode == OPCODE_STATUS) return "STATUS";
        if (opcode == OPCODE_UNASSIGNED) return "UNASSIGNED";
        if (opcode == OPCODE_NOTIFY) return "NOTIFY";
        if (opcode == OPCODE_UPDATE) return "UPDATE";
        return "N/A";
    }
} // namespace Dns