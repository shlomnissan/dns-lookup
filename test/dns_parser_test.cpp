// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <string>
#include <gtest/gtest.h>
#include <arpa/inet.h>

#include "dns/dns_parser.h"
#include "dns/dns_question.h"
#include "dns/types.h"
#include "common/exception.h"

using namespace Dns;
using namespace Common;

TEST(
    dns_parser_tests,
    ParsesMessageCorrectly
) {
    // TODO: implement
}

TEST(
    dns_parser_tests,
    ThrowsMessageIsTooShort
) {
    Header header {};
    header.id = htons(0xABCD);

    Buffer buffer {};
    buffer.write(
        reinterpret_cast<char*>(&header),
        sizeof(header) - 1 // 1 byte smaller than the header
    );

    EXPECT_THROW({
        DNSParser parser {buffer};
    }, MessageIsTooShort);
}