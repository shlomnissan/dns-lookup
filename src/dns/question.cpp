// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <arpa/inet.h>
#include <cstdint>
#include <sstream>

#include "dns/question.h"
#include "dns/types.h"

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
        question.type = htons(getTypeIDFromString(type));
        question.clazz = htons(/* internet = */ 1);

        auto name_len = question.name.getSize();
        buffer.write(question.name.getName().c_str(), name_len);
        buffer.write(reinterpret_cast<char*>(&question.type), sizeof(question.type));
        buffer.write(
            reinterpret_cast<char*>(&question.clazz), sizeof(question.clazz)
        );
    }

    auto Question::getTypeIDFromString(string_view type) -> uint16_t {
        if (type == "a") return TYPE_A;
        if (type == "ns") return TYPE_NS;
        if (type == "cname") return TYPE_CNAME;
        if (type == "mx") return TYPE_MX;
        if (type == "txt") return TYPE_TXT;
        if (type == "aaaa") return TYPE_AAAA;
        if (type == "any") return TYPE_ANY;

        throw InvalidQuestionType();
    }
} // namespace Dns
