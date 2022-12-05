// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <string>
#include <gtest/gtest.h>

#include "dns/dns_question.h"
#include "common/exception.h"

using namespace Dns;
using namespace Common;

// DNS request payload to www.example.com
const unsigned char dns_request[] = {
    0xab, 0xcd, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x03, 0x77, 0x77, 0x77, 0x07, 0x65, 0x78, 0x61,
    0x6d, 0x70, 0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00, 0x00,
    0x01, 0x00, 0x01
};

TEST(
    dns_question_test,
    GeneratesMessageCorrectly
) {
    DNSQuestion question {0xABCD, "www.example.com", "a"};
    auto data = question.buffer.getData();

    for (int i = 0; i < sizeof(dns_request); ++i) {
        EXPECT_EQ(data[i], static_cast<char>(dns_request[i]));
    }
    EXPECT_EQ(question.buffer.getSize(), sizeof(dns_request));
}

TEST(
    dns_question_test,
    ThrowsExceptionInvalidQuestionType
) {
    std::string invalid_type = "abc";

    EXPECT_THROW({
        DNSQuestion question(0xABCD, "example.com", invalid_type);
    }, Common::InvalidQuestionType);
}