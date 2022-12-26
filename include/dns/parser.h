// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_DNS_PARSER_H
#define DNS_LOOKUP_DNS_PARSER_H

#include <cstdint>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "dns/types.h"
#include "network/buffer.h"

namespace Dns {
    using Network::Buffer;
    using std::string;
    using std::stringstream;

    class Parser {
    public:
        explicit Parser(uint16_t id, const Buffer& buffer);

        [[nodiscard]] auto getOpcode() const { return header.opcode; }
        [[nodiscard]] auto getRcode() const { return header.rcode; }
        [[nodiscard]] auto getId() const { return header.id; }
        [[nodiscard]] auto getQuestionCount() const -> int { return header.qdcount; }
        [[nodiscard]] auto getQuestionType() const { return question.type; }
        [[nodiscard]] auto getHostname() const { return question.name.getHostname(); }
        [[nodiscard]] auto getAnswers() const -> vector<t_resource_record> { return answer_rrs; }
        [[nodiscard]] auto getAnswerCount() const -> int { return answer_count; }

        [[nodiscard]] auto recordToString(t_resource_record record) const -> string;

    private:
        uint16_t id;
        uint16_t answer_count = 0;
        Buffer buffer;
        t_header header {};
        t_question question {};
        vector<t_resource_record> answer_rrs;

        auto parseMessage() -> void;
    };

    struct IDMismatch : public std::runtime_error {
        IDMismatch(uint16_t req_id, uint16_t res_id) : std::runtime_error("") {
            std::stringstream ss;
            ss << "The DNS request ID ";
            ss << "(0x" << std::hex << req_id << ") ";
            ss << "doesn't match the response ID ";
            ss << "(0x" << std::hex << res_id << ").";
            static_cast<std::runtime_error&>(*this) = std::runtime_error(ss.str());
        }
    };

    struct MessageIsTruncated : public std::runtime_error {
        MessageIsTruncated() :
            std::runtime_error(
                "The DNS message is truncated. DNS over TCP is not supported."
            ) {}
    };

    struct MessageIsTooShort : public std::runtime_error {
        MessageIsTooShort() :
            std::runtime_error(
                "The DNS message is too short to be valid."
            ) {}
    };
} // namespace Dns

#endif // DNS_LOOKUP_DNS_PARSER_H