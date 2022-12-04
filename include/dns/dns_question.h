// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_DNS_QUESTION_H
#define DNS_LOOKUP_DNS_QUESTION_H

#include <string>
#include <string_view>
#include <cstdint>
#include <limits>
#include <array>

#include "common/buffer.h"

namespace Dns {
    class DNSQuestion {
    public:
        Common::Buffer buffer;

        DNSQuestion(
            uint16_t id,
            std::string_view hostname,
            std::string_view type
        );

    private:
        uint16_t id;

        void buildMessage(std::string_view hostname, std::string_view type);
        [[nodiscard]] static std::string formatHostname(std::string_view hostname);
        [[nodiscard]] static uint16_t getTypeIDFromString(std::string_view type);
    };
}

#endif  // DNS_LOOKUP_DNS_QUESTION_H
