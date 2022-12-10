// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <cstdint>
#include <gtest/gtest.h>
#include <limits>
#include <string>

#include "network/buffer.h"

using namespace std;
using namespace Network;

TEST(buffer_test, StoresDataCorrectly) {
    string data = "example.com";

    Buffer buffer {};
    buffer.write(data.c_str(), static_cast<int>(data.size()));

    EXPECT_EQ(strcmp(data.c_str(), buffer.getData()), 0);
}

TEST(buffer_test, ThrowsExceptionBufferOutOfRange) {
    auto size {numeric_limits<uint16_t>::max()};
    string data(size, ' ');

    Buffer buffer {};
    buffer.write(data.c_str(), size);

    EXPECT_THROW({ buffer.write(data.c_str(), 1); }, BufferOutOfRange);
}