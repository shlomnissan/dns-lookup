// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <arpa/inet.h>
#include <cstdint>
#include <cstring>
#include <iostream>

#include "dns/dns_utilities.h"
#include "dns/parser.h"

namespace Dns {
    using std::cout;

    Parser::Parser(Buffer buffer) {
        if (buffer.getSize() < sizeof(t_header)) { throw MessageIsTooShort(); }

        parseMessage(buffer);
    }

    auto Parser::parseMessage(Buffer& buffer) -> void {
        // TODO: throw an exception if there's no header

        memcpy(&header, buffer.getData(), sizeof(header));
        header.id = ntohs(header.id);
        header.qdcount = ntohs(header.qdcount);
        header.ancount = ntohs(header.ancount);
        header.nscount = ntohs(header.nscount);
        header.arcount = ntohs(header.arcount);

        buffer.seek(sizeof(header));

        if (header.qdcount) {
            question.name.initWithData(buffer, buffer.getCurrData());
            buffer.seek(question.name.getSize());
            question.type = buffer.read_bytes<uint16_t>();
            question.qclass = buffer.read_bytes<uint16_t>();
        } else {
            // TODO: throw an exception
        }

        for (int i = 0; i < header.ancount; ++i) {
            t_resource_record record;
            record.name.initWithData(buffer, buffer.getCurrData());
            buffer.seek(record.name.getSize());
            record.type = buffer.read_bytes<uint16_t>();
            record.qclass = buffer.read_bytes<uint16_t>();
            record.ttl = buffer.read_bytes<uint32_t>();
            record.length = buffer.read_bytes<uint16_t>();

            cout << "\n";
            cout << "Name: " << record.name.getHostname() << '\n';
            cout << "Type: " << type_to_string(record.type) << '\n';
            cout << "Class: " << record.qclass << '\n';
            cout << "TTL: " << record.ttl << '\n';
            cout << "Data len: " << record.length << '\n';

            // TODO: process data
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