// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <arpa/inet.h>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <sstream>

#include "dns/parser.h"

namespace Dns {
    Parser::Parser(const Buffer& buffer) : buffer(buffer) { parseMessage(); }

    auto Parser::parseMessage() -> void {
        if (buffer.getSize() < sizeof(t_header)) { throw MessageIsTooShort(); }

        memcpy(&header, buffer.getData(), sizeof(header));
        header.id = ntohs(header.id);
        header.qdcount = ntohs(header.qdcount);
        header.ancount = ntohs(header.ancount);
        header.nscount = ntohs(header.nscount);
        header.arcount = ntohs(header.arcount);

        if (header.tc) { throw MessageIsTruncated(); }

        answer_count = header.ancount + header.nscount + header.arcount;

        buffer.seek(sizeof(header));

        if (header.qdcount) {
            question.name.initWithData(buffer, buffer.getCurrData());
            buffer.seek(question.name.getSize());
            question.type = buffer.read_bytes<uint16_t>();
            question.qclass = buffer.read_bytes<uint16_t>();
        }

        for (int i = 0; i < answer_count; ++i) {
            t_resource_record record;
            record.name.initWithData(buffer, buffer.getCurrData());
            buffer.seek(record.name.getSize());

            record.type = buffer.read_bytes<uint16_t>();
            record.qclass = buffer.read_bytes<uint16_t>();
            record.ttl = buffer.read_bytes<uint32_t>();
            record.length = buffer.read_bytes<uint16_t>();
            record.data = {buffer.getCurrData(), record.length};
            buffer.seek(record.length);

            answer_rrs.emplace_back(record);
        }
    }

    auto Parser::recordToString(t_resource_record record) const -> string {
        string output;
        if (record.type == TYPE_A) {
            // parse A record
            for (int i = 0; i < 4; ++i) {
                auto byte = record.data.read_bytes<uint8_t>();
                output += std::to_string(static_cast<int>(byte));
                if (i != 3) output += ".";
            }
        } else if (record.type == TYPE_AAAA) {
            // parse AAAA record
            std::stringstream ss {};
            ss << std::hex;
            for (int i = 0; i < 8; ++i) {
                ss << record.data.read_bytes<uint16_t>();
                if (i != 7) ss << ":";
            }
            output = ss.str();
        } else if (record.type == TYPE_MX) {
            // parse MX record
            auto preference = record.data.read_bytes<uint16_t>();
            output += std::to_string(static_cast<int>(preference)) + " ";
            output += Name(buffer, record.data.getCurrData()).getHostname();
        } else {
            throw InvalidAnswerType();
        }

        // TODO: implement NS
        // TODO: implement CNAME
        // TODO: implement TXT
        // TODO: implement ANY

        return output;
    }
} // namespace Dns