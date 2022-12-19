// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <iostream>

#include "dns/dns_utilities.h"
#include "dns/parser.h"
#include "dns/question.h"
#include "network/endpoint.h"
#include "network/socket.h"

auto printResult(const Dns::Parser& parser) -> void;

auto main(int argc, char* argv[]) -> int {
    using namespace Dns;
    using namespace Network;
    using std::cerr;
    using std::cout;

    if (argc < 3) {
        cout << "Usage: dns_lookup HOSTNAME TYPE\n";
        cout << "Example: dns_lookup example.com aaaa\n";
        return 1;
    }

    try {
        cout << "\n;;DNS LOOKUP (" << get_dns_server() << "#53)\n";

        Question question {0xABCD, argv[1], argv[2]};
        Endpoint endpoint {get_dns_server(), "53"};
        Socket socket {endpoint};

        if (!socket.send(question.buffer)) {
            cerr << "Failed to send DNS question.\n";
            exit(EXIT_FAILURE);
        }

        Parser parser {socket.receive()};
        printResult(parser);
    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}

auto printResult(const Dns::Parser& parser) -> void {
    using std::cout;

    cout << "Type: " << Dns::opcode_to_str(parser.getOpcode()) << "; ";
    cout << "Status: " << Dns::rcode_to_str(parser.getRcode()) << "; ";
    cout << "ID: 0x" << std::hex << std::uppercase << parser.getId() << "\n";

    if (parser.getQuestionCount()) {
        cout << "\n;;QUESTION\n";
        cout << parser.getHostname() << ".\t\t";
        cout << "IN\t";
        cout << Dns::type_to_str(parser.getQuestionType()) << '\n';
    }

    if (parser.getAnswerCount()) {
        cout << "\n;;ANSWERS (" << parser.getAnswerCount() << ")\n";
        for (const auto& record : parser.getAnswers()) {
            cout << record.name.getHostname() << ".\t";
            cout << std::dec << record.ttl << '\t' << "IN\t";
            cout << Dns::type_to_str(record.type) << '\t';
            cout << parser.recordToString(record) << '\n';
        }
    } else {
        cout << "\nNo answers found.\n";
    }
}
