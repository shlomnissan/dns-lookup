// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <iostream>

#include "dns/dns_utilities.h"
#include "dns/parser.h"
#include "dns/question.h"
#include "network/endpoint.h"
#include "network/socket.h"

auto main(int argc, char* argv[]) -> int {
    using namespace Dns;
    using namespace Network;
    using std::cerr;
    using std::cout;

    cout << "DNS lookup v1.0\n";
    if (argc < 3) {
        cout << "Usage: dns_lookup HOSTNAME TYPE\n";
        cout << "Example: dns_lookup example.com aaaa\n";
        return 1;
    }

    try {
        Question question {0xABCD, argv[1], argv[2]};
        Endpoint endpoint {get_dns_server(), "53"};
        Socket socket {endpoint};

        if (!socket.send(question.buffer)) {
            cerr << "Failed to send DNS question.\n";
            exit(EXIT_FAILURE);
        }

        Parser parser {socket.receive()};
        parser.prettyPrint();

        // TODO: get header
        // TODO: get question
        // TODO: get answers

        // TODO: print data
    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
