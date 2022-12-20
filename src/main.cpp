// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gflags/gflags.h>
#include <iostream>

#include "dns/dns_utilities.h"
#include "dns/parser.h"
#include "dns/question.h"

#include "network/endpoint.h"
#include "network/net_utilities.h"
#include "network/socket.h"

#include "flags.h"

auto printResult(const Dns::Parser& parser) -> void;

auto main(int argc, char* argv[]) -> int {
    gflags::SetUsageMessage("dns_lookup -host example.com -type A -server 8.8.8.8");
    gflags::SetVersionString("1.0.0");
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    auto server = FLAGS_server.empty() ? Dns::get_dns_server() : FLAGS_server;
    auto type = Network::to_uppercase(FLAGS_type); 

    try {
        std::cout << "\n;;DNS LOOKUP (" << server << "#53)\n";

        Dns::Question question {0xABCD, FLAGS_host, type};
        Network::Endpoint endpoint {server, "53"};
        Network::Socket socket {endpoint};

        if (!socket.send(question.buffer)) {
            std::cerr << "Failed to send DNS question.\n";
            exit(EXIT_FAILURE);
        }

        Dns::Parser parser {socket.receive()};
        printResult(parser);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
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
    } else {
        cout << "\nNo question found.\n";
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
