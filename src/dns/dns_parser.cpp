// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <arpa/inet.h>
#include <cstring>
#include <iostream>

#include "dns/dns_parser.h"
#include "dns/dns_utilities.h"

namespace Dns {
    DNSParser::DNSParser(const Buffer& buffer) {
        if (buffer.getSize() < sizeof(Header)) { throw MessageIsTooShort(); }

        parseMessage(buffer.getData(), buffer.getSize());
    }

    auto DNSParser::parseMessage(const char* msg, uint16_t msg_size) -> void {
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

    auto DNSParser::prettyPrint() const -> void {
        std::cout << "\n;;HEADER\n";
        std::cout << "opcode: " << opcode_to_string(header.opcode) << ", "
                  << "status: " << rcode_to_string(header.rcode) << ", "
                  << "id: " << std::hex << header.id << '\n';
        std::cout << "flags:";
        if (header.qr) std::cout << " qr";
        if (header.rd) std::cout << " rd";
        if (header.ra) std::cout << " ra";
        std::cout << "; ";
        std::cout << "QUERY: " << header.qdcount << ", ";
        std::cout << "ANSWER: " << header.ancount << ", ";
        std::cout << "AUTHORITY: " << header.nscount << ", ";
        std::cout << "ADDITIONAL: " << header.arcount << "\n";

        if (header.qdcount) {
            std::cout << "\n;;QUSTION SECTION\n";
            std::cout << question.name.getHostname() << ".";
            std::cout << "\t\t"
                      << "IN";
            std::cout << "\t\t" << type_to_string(question.type);
            std::cout << "\n";
        }

        if (header.ancount) { std::cout << "\n;;ANSWER SECTION\n"; }
    }
} // namespace Dns