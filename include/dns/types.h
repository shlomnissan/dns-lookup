// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_TYPES_H
#define DNS_LOOKUP_TYPES_H

#include <cstdint>

#include "dns/name.h"

namespace Dns {
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

        uint16_t id;        // identification number

        uint8_t rd :1;      // recursion desired
        uint8_t tc :1;      // truncated message
        uint8_t aa :1;      // authoritative answer
        uint8_t opcode :4;  // type of operation
        uint8_t qr :1;      // query or response
        uint8_t rcode :4;   // response code
        uint8_t cd :1;      // checking disabled
        uint8_t ad :1;      // authenticated data
        uint8_t z :1;       // reserved
        uint8_t ra :1;      // recursion available

        uint16_t qdcount;   // number of questions
        uint16_t ancount;   // number of answers
        uint16_t nscount;   // number of authority entries
        uint16_t arcount;   // number of resource entries
    };

    struct Question {
        Name name;
        uint16_t qtype;     // question type
        uint16_t qclass;    // question class
    };
}

#endif  // DNS_LOOKUP_TYPES_H
