// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <arpa/inet.h>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <sstream>

#include "dns/parser.h"

namespace Dns {
    Parser::Parser(uint16_t id, const Buffer& buffer) : id(id), buffer(buffer) {
        parseMessage();
    }

    auto Parser::parseMessage() -> void {
        if (buffer.getSize() < sizeof(t_header)) { throw MessageIsTooShort(); }

        memcpy(&header, buffer.data(), sizeof(header));
        header.id = ntohs(header.id);
        header.qdcount = ntohs(header.qdcount);
        header.ancount = ntohs(header.ancount);
        header.nscount = ntohs(header.nscount);
        header.arcount = ntohs(header.arcount);

        if (header.id != id) { throw IDMismatch(id, header.id); }
        if (header.tc) { throw MessageIsTruncated(); }

        answer_count = header.ancount + header.nscount + header.arcount;

        buffer.seek(sizeof(header));

        if (header.qdcount) {
            question.name.initWithData(buffer, buffer.currData());
            buffer.seek(question.name.getSize());
            question.type = buffer.readBytes<uint16_t>();
            question.qclass = buffer.readBytes<uint16_t>();
        }

        for (int i = 0; i < answer_count; ++i) {
            t_resource_record record;
            record.name.initWithData(buffer, buffer.currData());
            buffer.seek(record.name.getSize());

            record.type = buffer.readBytes<uint16_t>();
            record.qclass = buffer.readBytes<uint16_t>();
            record.ttl = buffer.readBytes<uint32_t>();
            record.length = buffer.readBytes<uint16_t>();
            record.data = {buffer.currData(), record.length};
            buffer.seek(record.length);

            answer_rrs.emplace_back(record);
        }
    }

    auto Parser::recordToString(t_resource_record record) const -> string {
        string output;

        switch (record.type) {
            case TYPE_A: {
                for (int i = 0; i < 4; ++i) {
                    auto byte = record.data.readBytes<uint8_t>();
                    output += std::to_string(static_cast<int>(byte));
                    if (i != 3) output += ".";
                }
            } break;
            case TYPE_AAAA: {
                std::stringstream ss {};
                ss << std::hex;
                for (int i = 0; i < 8; ++i) {
                    ss << record.data.readBytes<uint16_t>();
                    if (i != 7) ss << ":";
                }
                output += ss.str();
            } break;
            case TYPE_MX: {
                auto preference = record.data.readBytes<uint16_t>();
                output += std::to_string(static_cast<int>(preference)) + " ";
                output += Name(buffer, record.data.currData()).getHostname();
            } break;
            case TYPE_NS:
            case TYPE_CNAME:
            case TYPE_SOA:
            case TYPE_TXT:
            case TYPE_ANY: {
                output += Name(buffer, record.data.currData()).getHostname();
            } break;
            default: {
                auto type_str = std::to_string(record.type);
                output += "Type " + type_str + " is not supported.\n";
            } break;
        }

        return output;
    }
} // namespace Dns