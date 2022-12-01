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
        std::cout << "\nID = 0x" << std::hex << header.id << '\n'; 
        std::cout << "Opcode = " << opcodeToString() << '\n';
        std::cout << "Type = " << (header.qr == 0 ? "Query" : "Response" ) << '\n'; 
        
        if (header.qr == 1) {
            std::cout << "Response = " << rcodeToString() << "\n\n";
        }

        std::cout << "(AA) Authoritative Answer = " << (header.aa ? "1" : "0") << '\n';
        std::cout << "(TC) Turncated = " << (header.tc ? "1" : "0") << '\n';
        std::cout << "(RD) Recursion Desired = " << (header.rd ? "1" : "0") << '\n';
        std::cout << "(RA) Recursion Available = " << (header.ra ? "1" : "0") << '\n';
    }

    std::string DNSParser::opcodeToString() const {
        switch (header.opcode) {
            case Header::Query: return "Query";
            case Header::Status: return "Status";
            case Header::Notify: return "Notify";
            case Header::Update: return "Update";
            default: return "Not implemented or deprecated";
        }
    }

    std::string DNSParser::rcodeToString() const {
        switch (header.rcode) {
            case Header::NoError: return "Success";
            case Header::FormatError: return "Format error";
            case Header::ServerFailure: return "Server failure";
            case Header::NonExistentDomain: return "Non-existent Domain";
            case Header::QueryRefused: return "Query refused"; 
            default: return "Not implemented or deprecated";
        }
    }
}