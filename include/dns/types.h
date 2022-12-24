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
    static constexpr uint8_t TYPE_SOA = 6;
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
    };
} // namespace Dns

#endif // DNS_LOOKUP_TYPES_H
