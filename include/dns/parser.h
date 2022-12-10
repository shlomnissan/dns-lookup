// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_DNS_PARSER_H
#define DNS_LOOKUP_DNS_PARSER_H

#include <string>

#include "dns/types.h"
#include "network/buffer.h"

namespace Dns {
    using Network::Buffer;

    class Parser {
    public:
        explicit Parser(const Buffer& buffer);

        // TODO: get question

        // TODO: get answers

        void prettyPrint() const;

    private:
        t_header header {};
        t_question question {};

        auto parseMessage(const char* msg, uint16_t msg_size) -> void;
    };

    struct MessageIsTooShort : public std::exception {
        const char* what() const throw() override {
            return "The DNS message is too short to be valid.";
        }
    };
} // namespace Dns

#endif // DNS_LOOKUP_DNS_PARSER_H