// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_DNS_PARSER_H
#define DNS_LOOKUP_DNS_PARSER_H

#include <vector>

#include "dns/types.h"
#include "network/buffer.h"

namespace Dns {
    using Network::Buffer;

    class Parser {
    public:
        explicit Parser(const Buffer& buffer);

        // TODO: get header

        // TODO: get question

        // TODO: get answers

        void prettyPrint() const;

    private:
        Buffer buffer;

        t_header header {};
        t_question question {};

        vector<t_resource_record> answer_rrs;

        auto parseMessage() -> void;
    };

    struct MessageIsTooShort : public std::exception {
        const char* what() const throw() override {
            return "The DNS message is too short to be valid.";
        }
    };
} // namespace Dns

#endif // DNS_LOOKUP_DNS_PARSER_H