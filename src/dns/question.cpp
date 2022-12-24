// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <arpa/inet.h>
#include <cstdint>
#include <sstream>

#include "dns/question.h"
#include "dns/types.h"

#include "network/net_utilities.h"

namespace Dns {
    Question::Question(uint16_t id, string_view hostname, string_view type)
        : id(id) {
        buildMessage(hostname, type);
    }

    auto Question::buildMessage(string_view hostname, string_view type) -> void {
        t_header header {};
        header.id = htons(id);
        header.rd = 1;
        header.qdcount = htons(1);
        buffer.write(reinterpret_cast<char*>(&header), sizeof(header));

        t_question question {};
        question.name.initWithHostname(hostname);
        question.type = htons(getTypeIDFromString(Network::to_uppercase(type)));
        question.qclass = htons(/* internet = */ 1);

        auto name_len = question.name.getSize();
        buffer.write(question.name.getName().c_str(), name_len);
        buffer.write(reinterpret_cast<char*>(&question.type), sizeof(question.type));
        buffer.write(
            reinterpret_cast<char*>(&question.qclass), sizeof(question.qclass)
        );
    }

    auto Question::getTypeIDFromString(string_view type) -> uint16_t {
        if (type == "A") return TYPE_A;
        if (type == "NS") return TYPE_NS;
        if (type == "CNAME") return TYPE_CNAME;
        if (type == "MX") return TYPE_MX;
        if (type == "TXT") return TYPE_TXT;
        if (type == "AAAA") return TYPE_AAAA;
        if (type == "ANY") return TYPE_ANY;

        throw InvalidQuestionType();
    }
} // namespace Dns
