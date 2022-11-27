// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <iostream>
#include <unistd.h>

#include "dns/dns_question.h"
#include "dns/dns_utilities.h"
#include "network/socket.h"

using namespace Dns;
using namespace Network;

int main(int argc, char* argv[]) {
    std::cout << "DNS query v1.0\n";
    if (argc < 3) {
        std::cout << "Usage: dns_lookup HOSTNAME TYPE\n";
        std::cout << "Example: dns_lookup example.com aaaa\n";
        exit(EXIT_SUCCESS);
    }

    try {
        DNSQuestion question {0xABCD, argv[1], argv[2]};

        Socket socket {{get_dns_server(), "53"}};
        if (!socket.send(question.buffer)) {
            std::cerr << "Failed to send DNS question.\n";
            exit(EXIT_FAILURE);
        }

        auto buffer = socket.receive();
        // TODO: Parse data
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
