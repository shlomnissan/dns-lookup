// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_TYPES_H
#define DNS_LOOKUP_TYPES_H

#include <cassert>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

#include "dns/name.h"
#include "network/buffer.h"

namespace Dns {
    using Network::Buffer;

    static constexpr uint8_t TYPE_A = 1;
    static constexpr uint8_t TYPE_NS = 2;
    static constexpr uint8_t TYPE_CNAME = 5;
    static constexpr uint8_t TYPE_MX = 15;
    static constexpr uint8_t TYPE_TXT = 16;
    static constexpr uint8_t TYPE_AAAA = 28;
    static constexpr uint8_t TYPE_ANY = 255;

    static constexpr uint8_t RCODE_NOERROR = 0;
    static constexpr uint8_t RCODE_FORMERR = 1;
    static constexpr uint8_t RCODE_SERVFAIL = 2;
    static constexpr uint8_t RCODE_NXDOMAIN = 3;
    static constexpr uint8_t RCODE_NOTIMP = 4;
    static constexpr uint8_t RCODE_REFUSED = 3;

    static constexpr uint8_t OPCODE_QUERY = 0;
    static constexpr uint8_t OPCODE_IQUERY = 1;
    static constexpr uint8_t OPCODE_STATUS = 2;
    static constexpr uint8_t OPCODE_UNASSIGNED = 3;
    static constexpr uint8_t OPCODE_NOTIFY = 4;
    static constexpr uint8_t OPCODE_UPDATE = 5;

    struct t_header {
        uint16_t id;

        uint8_t rd : 1;
        uint8_t tc : 1;
        uint8_t aa : 1;
        uint8_t opcode : 4;
        uint8_t qr : 1;
        uint8_t rcode : 4;
        uint8_t z : 3;
        uint8_t ra : 1;

        uint16_t qdcount;
        uint16_t ancount;
        uint16_t nscount;
        uint16_t arcount;
    };

    struct t_question {
        Name name;
        uint16_t type;
        uint16_t qclass;
    };

    struct t_resource_record {
        Name name;
        uint16_t type;
        uint16_t qclass;
        uint32_t ttl;
        uint16_t length;
        Buffer data;

        auto dataString(const Buffer& buffer) -> std::string {
            if (length == 0 || data.getSize() != length) {
                // TODO: raise exception
            }

            std::string output;
            if (type == TYPE_A) {
                if (length != 4) {
                    // TODO: raise an exception
                }
                for (int i = 0; i < 4; ++i) {
                    auto byte = data.read_bytes<uint8_t>();
                    output += std::to_string(static_cast<int>(byte));
                    if (i != 3) output += ".";
                }
            } else if (type == TYPE_AAAA) {
                if (length != 16) {
                    // TODO: raise an exception
                }
                std::stringstream ss {};
                ss << std::hex;
                for (int i = 0; i < 8; ++i) {
                    ss << data.read_bytes<uint16_t>();
                    if (i != 7) ss << ":";
                }
                output = ss.str();
            } else if (type == TYPE_MX) {
                auto preference = data.read_bytes<uint16_t>();
                output += std::to_string(static_cast<int>(preference)) + " "; 
                output += Name(buffer, data.getCurrData()).getHostname();
            }
            // TODO: implement NS
            // TODO: implement CNAME
            // TODO: implement TXT
            // TODO: implement ANY
            return output;
        }
    };
} // namespace Dns

#endif // DNS_LOOKUP_TYPES_H
