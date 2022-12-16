// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <cstring>
#include <gtest/gtest.h>
#include <iostream>

#include "dns/name.h"
#include "network/buffer.h"

using namespace Dns;

// DNS request payload to www.example.com
const unsigned char dns_request[] = {
    0xab, 0xcd, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x03, 0x77, 0x77, 0x77, 0x07, 0x65, 0x78, 0x61, 0x6d, 0x70,
    0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00, 0x00, 0x01, 0x00, 0x01};

// DNS response payload for www.example.com
const unsigned char dns_response[] {
    0xab, 0xcd, 0x81, 0x80, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x03,
    0x77, 0x77, 0x77, 0x07, 0x65, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x03, 0x63,
    0x6f, 0x6d, 0x00, 0x00, 0x01, 0x00, 0x01, 0xc0, 0x0c, 0x00, 0x01, 0x00, 0x01,
    0x00, 0x00, 0x1a, 0xfb, 0x00, 0x04, 0x5d, 0xb8, 0xd8, 0x22};

TEST(dns_name_test, InitNameWithDataNoCompressionLabels) {
    Buffer message {(const char*)dns_request, sizeof(dns_request)};
    auto p = message.getData() + 12;

    Name name {};
    name.initWithData(message, p);

    EXPECT_EQ(name.getSize(), 17);
    EXPECT_EQ(name.getHostname(), "www.example.com");
    EXPECT_EQ(strcmp(name.getName().c_str(), p), 0);
}

TEST(dns_name_test, InitNameWithDataWithCompressionLabels) {
    Buffer message {(const char*)dns_response, sizeof(dns_response)};
    auto p = message.getData() + 33;

    Name name {};
    name.initWithData(message, p);

    EXPECT_EQ(name.getSize(), 2); // each compression label is 2-bytes
    EXPECT_EQ(name.getHostname(), "www.example.com");
}

TEST(dns_name_test, InitNameWithHostname) {
    Name name {};
    name.initWithHostname("www.example.com");

    EXPECT_EQ(name.getSize(), 17);
    EXPECT_EQ(name.getHostname(), "www.example.com");
    EXPECT_EQ(strcmp(name.getName().c_str(), (const char*)dns_request + 12), 0);
}