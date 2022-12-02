// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>
#include <iostream>
#include <cstring>

#include "dns/name.h"

using namespace Dns;

TEST(
    dns_name_test,
    GeneratesNameWithSimpleData
) {
    const char data_no_compression[] = {
        3, 'w', 'w', 'w',
        7, 'e', 'x', 'a', 'm', 'p', 'l', 'e',
        3, 'c', 'o', 'm',
        0,
        1, 2, 3, 4, 5, 6, 7, 8, 9
    };

    Name name(data_no_compression);

    EXPECT_EQ(name.getSize(), 17);
    EXPECT_EQ(name.getHostname(), "www.example.com");
    EXPECT_EQ(strcmp(name.getName().c_str(), data_no_compression), 0);
}