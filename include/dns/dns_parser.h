// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_DNS_PARSER_H
#define DNS_LOOKUP_DNS_PARSER_H

#include <string>

#include "dns/types.h"
#include "common/buffer.h"

namespace Dns {
    using namespace Common;

    class DNSParser {
    public:

        explicit DNSParser(const Buffer& buffer);

        // TODO: get question

        // TODO: get answers

        void prettyPrint() const;

    private:
        Header header {};
        Question question {};

        void parseMessage(const char* msg, uint16_t msg_size);

        std::string opcodeToString() const;
        std::string rcodeToString() const;
    };
}

#endif  // DNS_LOOKUP_DNS_PARSER_H