// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <arpa/inet.h>
#include <cstdint>
#include <cstring>
#include <iostream>

#include "dns/dns_utilities.h"
#include "dns/parser.h"

// TODO: move to buffer
template <typename T> auto read_and_increment(const char** data) -> T {
    if (std::is_same_v<T, uint32_t>) {
        uint32_t v32 =
            **data << 24 | *(*data + 1) << 16 | *(*data + 2) << 8 | *(*data + 3);
        *data += 4;
        return v32;
    }
    if (std::is_same_v<T, uint16_t>) {
        uint16_t v16 = **data << 8 | *(*data + 1);
        *data += 2;
        return v16;
    }
}

namespace Dns {
    using std::cout;

    Parser::Parser(const Buffer& buffer) {
        if (buffer.getSize() < sizeof(t_header)) { throw MessageIsTooShort(); }

        parseMessage(buffer.getData(), buffer.getSize());
    }

    auto Parser::parseMessage(const char* msg, uint16_t msg_size) -> void {
        const char* iter = msg;

        memcpy(&header, iter, sizeof(header));
        header.id = ntohs(header.id);
        header.qdcount = ntohs(header.qdcount);
        header.ancount = ntohs(header.ancount);
        header.nscount = ntohs(header.nscount);
        header.arcount = ntohs(header.arcount);
        iter += sizeof(header);

        if (header.qdcount) {
            question.name.initWithData({msg, msg_size}, iter);
            iter += question.name.getSize();
            question.type = read_and_increment<uint16_t>(&iter);
            question.qclass = read_and_increment<uint16_t>(&iter);
        }

        for (int i = 0; i < header.ancount; ++i) {
            t_resource_record record;
            record.name.initWithData({msg, msg_size}, iter);
            iter += record.name.getSize();
            record.type = read_and_increment<uint16_t>(&iter);
            record.qclass = read_and_increment<uint16_t>(&iter);
            record.ttl = read_and_increment<uint32_t>(&iter);
            record.length = read_and_increment<uint16_t>(&iter); 

            // TODO: remove test and read data
            // --> potential TTL issue on reset
            cout << "\n";
            cout << "Name: " << record.name.getHostname() << '\n';
            cout << "Type: " << type_to_string(record.type) << '\n';
            cout << "Class: " << record.qclass << '\n';
            cout << "TTL: " << record.ttl << '\n';
            cout << "Data len: " << record.length << '\n';
        }
    }

    auto Parser::prettyPrint() const -> void {
        cout << "\n;;HEADER\n";
        cout << "opcode: " << opcode_to_string(header.opcode) << ", "
             << "status: " << rcode_to_string(header.rcode) << ", "
             << "id: " << std::hex << header.id << '\n';
        cout << "flags:";
        if (header.qr) cout << " qr";
        if (header.rd) cout << " rd";
        if (header.ra) cout << " ra";
        cout << "; ";
        cout << "QUERY: " << header.qdcount << ", ";
        cout << "ANSWER: " << header.ancount << ", ";
        cout << "AUTHORITY: " << header.nscount << ", ";
        cout << "ADDITIONAL: " << header.arcount << "\n";

        if (header.qdcount) {
            cout << "\n;;QUSTION SECTION\n";
            cout << question.name.getHostname() << ".";
            cout << "\t\t"
                 << "IN";
            cout << "\t" << type_to_string(question.type);
            cout << "\n";
        }

        if (header.ancount) { cout << "\n;;ANSWER SECTION\n"; }
    }
} // namespace Dns