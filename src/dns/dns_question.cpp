// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <sstream>
#include <arpa/inet.h>

#include "common/exception.h"
#include "dns/dns_question.h"
#include "dns/types.h"

namespace Dns {
    DNSQuestion::DNSQuestion(
        uint16_t id,
        std::string_view hostname,
        std::string_view type
    ) : id(id) {
        buildMessage(hostname, type);
    }

    void DNSQuestion::buildMessage(std::string_view hostname, std::string_view type) {
        Header header {};
        header.id = htons(id);
        header.rd = 1;
        header.qdcount = htons(1);
        buffer.write(reinterpret_cast<char*>(&header), sizeof(header));

        Question question {};
        question.name.initWithHostname(hostname);
        question.qtype = htons(getTypeIDFromString(type));
        question.qclass = htons(/* internet = */ 1);

        auto name_len = question.name.getSize();
        buffer.write(question.name.getName().c_str(), name_len);
        buffer.write(reinterpret_cast<char*>(&question.qtype), sizeof(question.qtype));
        buffer.write(reinterpret_cast<char*>(&question.qclass), sizeof(question.qclass));
    }

    uint16_t DNSQuestion::getTypeIDFromString(std::string_view type) {
        if (type == "a") return TYPE_A;
        if (type == "mx") return TYPE_MX;
        if (type == "txt") return TYPE_TXT;
        if (type == "aaaa") return TYPE_AAAA;
        if (type == "any") return TYPE_ANY;

        throw Common::InvalidQuestionType();
    }
}
