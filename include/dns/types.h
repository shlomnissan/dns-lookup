// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_TYPES_H
#define DNS_LOOKUP_TYPES_H

#include <cstdint>

#include "dns/name.h"

namespace Dns {
    static constexpr uint8_t TYPE_A     = 1;
    static constexpr uint8_t TYPE_MX    = 15;
    static constexpr uint8_t TYPE_TXT   = 16;
    static constexpr uint8_t TYPE_AAAA  = 28;
    static constexpr uint8_t TYPE_ANY   = 255;

    struct Header {
        enum Opcodes {
            Query,
            InverseQuery,
            Status,
            Unassigned,
            Notify,
            Update,
        };

        enum Rcodes {
            NoError,
            FormatError,
            ServerFailure,
            NonExistentDomain,
            NotImplemented,
            QueryRefused,
        };

        uint16_t id;

        uint8_t rd :1;
        uint8_t tc :1;
        uint8_t aa :1;
        uint8_t opcode :4;
        uint8_t qr :1;
        uint8_t rcode :4;
        uint8_t z :3;
        uint8_t ra :1;

        uint16_t qdcount;
        uint16_t ancount;
        uint16_t nscount;
        uint16_t arcount;
    };

    struct Question {
        Name name;
        uint16_t type;
        uint16_t clazz;
    };

    struct ResourceRecord {
        Name name;
        uint16_t type;
        uint16_t clazz;
        uint32_t ttl;
        uint16_t length;
    };
}

#endif  // DNS_LOOKUP_TYPES_H
