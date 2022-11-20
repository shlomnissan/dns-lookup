// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "dns/dns_question.h"
#include "dns/types.h"
#include "common/exception.h"

#include <sstream>
#include <arpa/inet.h>

namespace dns {
    DNSQuestion::DNSQuestion(
        uint16_t id,
        std::string_view hostname,
        std::string_view type
    ) : id(id) {
        buildMessage(formatHostName(hostname), getTypeIDFromString(type));
    }

    void DNSQuestion::buildMessage(std::string_view hostname, uint8_t type) {
        Header message_header {};
        message_header.id = htons(id);
        message_header.rd = 1;
        message_header.qdcount = htons(1);

        // TODO: add name
        // TODO: add query
    }

    std::string DNSQuestion::formatHostName(std::string_view hostname) {
        if (hostname.size() > 255) {
            throw Common::InvalidHostnameLength();
        }

        std::stringstream ss {hostname.data()};
        std::string output {};
        std::string buffer {};
        while (getline(ss, buffer, '.')) {
            output += std::to_string(size(buffer));
            output += buffer;
        }
        output += '\0';
        return output;
    }

    uint8_t DNSQuestion::getTypeIDFromString(std::string_view type) {
        if (type == "a") return TYPE_A;
        if (type == "mx") return TYPE_MX;
        if (type == "txt") return TYPE_TXT;
        if (type == "aaaa") return TYPE_AAAA;
        if (type == "any") return TYPE_ANY;

        throw Common::InvalidQuestionType();
    }
}
