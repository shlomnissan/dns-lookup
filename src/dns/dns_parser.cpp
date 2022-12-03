// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <iostream>
#include <cstring>
#include <arpa/inet.h>

#include "dns/dns_parser.h"
#include "common/exception.h"


namespace Dns {
    DNSParser::DNSParser(const Buffer& buffer) {
        if (buffer.getSize() < sizeof(Header)) {
            throw MessageIsTooShort();
        }

        parseMessage(buffer.getData(), buffer.getSize());
    }

    void DNSParser::parseMessage(const char* msg, uint16_t msg_size) {
        const unsigned char* iter = (unsigned char*)msg;

        memcpy(&header, msg, sizeof(header)); 
        header.id = ntohs(header.id);
        header.qdcount = ntohs(header.qdcount);
        header.ancount = ntohs(header.ancount);
        header.nscount = ntohs(header.nscount);
        header.arcount = ntohs(header.arcount);
    }

    void DNSParser::prettyPrint() const {
        std::cout << "\n>> HEADER <<\n";
        std::cout << ";; ";
        std::cout << "opcode: " << opcodeToString() << ", "
                  << "status: " << rcodeToString() << ", "
                  << "id: " << std::hex << header.id << '\n'; 
        std::cout << ";; flags:";
        if (header.qr) std::cout << " qr";
        if (header.rd) std::cout << " rd";
        if (header.ra) std::cout << " ra";
        std::cout << "; ";
        std::cout << "QUERY: " << header.qdcount << ", ";
        std::cout << "ANSWER: " << header.ancount << ", ";
        std::cout << "AUTHORITY: " << header.nscount << ", ";
        std::cout << "ADDITIONAL: " << header.arcount << "\n";

        std::cout << "\n>> QUSTION SECTION\n";

        // TODO: print question
    }

    std::string DNSParser::opcodeToString() const {
        switch (header.opcode) {
            case Header::Query: return "QUERY";
            case Header::Status: return "STATUS";
            case Header::Notify: return "NOTIFY";
            case Header::Update: return "UPDATE";
            default: return "Not implemented or deprecated";
        }
    }

    std::string DNSParser::rcodeToString() const {
        switch (header.rcode) {
            case Header::NoError: return "NOERROR";
            case Header::FormatError: return "FORMATERROR";
            case Header::ServerFailure: return "SERVERFAILURE";
            case Header::NonExistentDomain: return "NXDOMAIN";
            case Header::QueryRefused: return "QUERYREFUSED"; 
            default: return "Not implemented or deprecated";
        }
    }
}