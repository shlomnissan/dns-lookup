// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_DNS_PARSER_H
#define DNS_LOOKUP_DNS_PARSER_H

#include <string>
#include <vector>

#include "dns/types.h"
#include "network/buffer.h"

namespace Dns {
    using Network::Buffer;
    using std::string;

    class Parser {
    public:
        explicit Parser(const Buffer& buffer);

        auto getOpcode() const { return header.opcode; }
        auto getRcode() const { return header.rcode; }
        auto getHostname() const { return question.name.getHostname(); }
        auto getQuestionType() const { return question.type; }
        auto getQuestionCount() const -> int { return header.qdcount; }
        auto getAnswerCount() const -> int { return header.ancount; }
        auto getAnswers() const -> vector<t_resource_record> { return answer_rrs; }
        auto getId() const { return header.id; }

        auto recordToString(t_resource_record record) const -> string;

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