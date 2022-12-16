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

    Parser::Parser(const Buffer& buffer) : buffer(buffer) { parseMessage(); }

    auto Parser::parseMessage() -> void {
        if (buffer.getSize() < sizeof(t_header)) { throw MessageIsTooShort(); }

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
            // TODO: throw an exception if there's no question count
        }

        for (int i = 0; i < header.ancount; ++i) {
            t_resource_record record;
            record.name.initWithData(buffer, buffer.getCurrData());
            buffer.seek(record.name.getSize());
            record.type = buffer.read_bytes<uint16_t>();
            record.qclass = buffer.read_bytes<uint16_t>();
            record.ttl = buffer.read_bytes<uint32_t>();
            record.length = buffer.read_bytes<uint16_t>();

            if (record.length > Buffer::max_size) {
                // TODO: throw an exception if the buffer is too small
            }

            record.data = {buffer.getCurrData(), record.length};
            buffer.seek(record.length);

            answer_rrs.emplace_back(record);
        }
    }

    auto Parser::prettyPrint() const -> void {
        cout << "\n;;HEADER\n";
        cout << "opcode: " << opcode_to_str(header.opcode) << ", "
             << "status: " << rcode_to_str(header.rcode) << ", "
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
            cout << '\t' << type_to_str(question.type);
        }

        cout << '\n';

        if (header.ancount) {
            cout << "\n;;ANSWER SECTION\n";
            for (auto record : answer_rrs) {
                cout << record.name.getHostname() << ".";
                cout << '\t';
                cout << std::dec << record.ttl << '\t';
                cout << "IN";
                cout << '\t' << type_to_str(record.type);
                cout << '\t' << record.dataString(buffer) << '\n';
            }
        }
    }
} // namespace Dns