// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <iostream>
#include <cstring>

#include "dns/name.h"

using namespace Dns;

// DNS request payload to www.example.com
const unsigned char dns_request[] = {
    0xab, 0xcd, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x03, 0x77, 0x77, 0x77, 0x07, 0x65, 0x78, 0x61,
    0x6d, 0x70, 0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00, 0x00,
    0x01, 0x00, 0x01
};

TEST(
    dns_name_test,
    InitNameWithRequestData
) {
    auto request = (const char*)dns_request + 12;

    Name name {};
    name.initWithData(request);

    EXPECT_EQ(name.getSize(), 17);
    EXPECT_EQ(name.getHostname(), "www.example.com");
    EXPECT_EQ(strcmp(name.getName().c_str(), request), 0);
}

// TODO: test with compression labels

TEST(
    dns_name_test,
    InitNameWithHostname
) {
    Name name {};
    name.initWithHostname("www.example.com");

    EXPECT_EQ(name.getSize(), 17);
    EXPECT_EQ(name.getHostname(), "www.example.com");
    EXPECT_EQ(strcmp(name.getName().c_str(), (const char*)dns_request + 12), 0);
}