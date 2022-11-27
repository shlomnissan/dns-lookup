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
    static constexpr uint8_t TYPE_A     = 1;
    static constexpr uint8_t TYPE_MX    = 15;
    static constexpr uint8_t TYPE_TXT   = 16;
    static constexpr uint8_t TYPE_AAAA  = 28;
    static constexpr uint8_t TYPE_ANY   = 255;

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
