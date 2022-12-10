// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <arpa/inet.h>
#include <gtest/gtest.h>
#include <iostream>
#include <string>

#include "dns/dns_parser.h"
#include "dns/types.h"
#include "network/buffer.h"

using namespace Dns;

// DNS response payload for www.example.com
const unsigned char dns_response[] {
    0xab, 0xcd, 0x81, 0x80, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x03,
    0x77, 0x77, 0x77, 0x07, 0x65, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x03, 0x63,
    0x6f, 0x6d, 0x00, 0x00, 0x01, 0x00, 0x01, 0xc0, 0x0c, 0x00, 0x01, 0x00, 0x01,
    0x00, 0x00, 0x1a, 0xfb, 0x00, 0x04, 0x5d, 0xb8, 0xd8, 0x22};

TEST(dns_parser_tests, ParsesMessageCorrectly) {
    Buffer buffer {(const char*)dns_response, sizeof(dns_response)};
    DNSParser parser {buffer};

    // TODO: add assertions
}

TEST(dns_parser_tests, ThrowsMessageIsTooShort) {
    Header header {};
    header.id = htons(0xABCD);

    Buffer buffer {};
    buffer.write(
        reinterpret_cast<char*>(&header),
        sizeof(header) - 1 // 1 byte smaller than the header
    );

    EXPECT_THROW({ DNSParser parser {buffer}; }, MessageIsTooShort);
}