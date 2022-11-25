// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "common/exception.h"
#include "dns/dns_question.h"
#include "dns/types.h"

#include <sstream>
#include <arpa/inet.h>

namespace dns {
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

        auto formattedHostname = formatHostname(hostname);
        buffer.write(formattedHostname.c_str(), formattedHostname.size());

        Question question {};
        question.qtype = htons(getTypeIDFromString(type)); 
        question.qclass = htons(/* internet = */ 1);
        buffer.write(reinterpret_cast<char*>(&buffer), sizeof(question));
    }

    std::string DNSQuestion::formatHostname(std::string_view hostname) {
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

    uint16_t DNSQuestion::getTypeIDFromString(std::string_view type) {
        if (type == "a") return TYPE_A;
        if (type == "mx") return TYPE_MX;
        if (type == "txt") return TYPE_TXT;
        if (type == "aaaa") return TYPE_AAAA;
        if (type == "any") return TYPE_ANY;

        throw Common::InvalidQuestionType();
    }
}
