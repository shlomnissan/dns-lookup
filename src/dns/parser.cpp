// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <arpa/inet.h>
#include <cstring>
#include <iostream>

#include "dns/dns_utilities.h"
#include "dns/parser.h"

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
            question.type = (iter[0] << 8) | iter[1];
            question.clazz = (iter[2] << 8) | iter[3];
            iter += 4;
        }

        // TODO: parse RRs
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
            cout << "\t\t" << type_to_string(question.type);
            cout << "\n";
        }

        if (header.ancount) { cout << "\n;;ANSWER SECTION\n"; }
    }
} // namespace Dns