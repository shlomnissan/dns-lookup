// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <string>
#include <gtest/gtest.h>

#include "dns/dns_question.h"
#include "common/exception.h"

using namespace Dns;
using namespace Common;

TEST(
    dns_question_test,
    GeneratesMessageCorrectly
) {
    DNSQuestion question {0xABCD, "example.com", "a"};

    unsigned char output[] = {
        0xAB, 0xCD,
        0x01, 0x00,
        0x00, 0x01,
        0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00,
        7, 'e', 'x', 'a', 'm', 'p', 'l', 'e',
        3, 'c', 'o', 'm',
        0,
        0x00, 0x01,
        0x00, 0x01
    };

    auto data = question.buffer.getData();
    for (int i = 0; i < sizeof(output); ++i) {
        EXPECT_EQ(data[i], static_cast<char>(output[i]));
    }
    EXPECT_EQ(question.buffer.getSize(), sizeof(output));
}

TEST(
    dns_question_test,
    ThrowsExceptionInvalidHostnameLength
) {
    std::string invalid_hostname(256, ' ');

    EXPECT_THROW({
        DNSQuestion question(0xABCD, invalid_hostname, "a");
    }, Common::InvalidHostnameLength);
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