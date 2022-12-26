// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_DNS_QUESTION_H
#define DNS_LOOKUP_DNS_QUESTION_H

#include <array>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string>
#include <string_view>

#include "network/buffer.h"

namespace Dns {
    using std::string;
    using std::string_view;

    class Question {
    public:
        Network::Buffer buffer;

        Question(uint16_t id, string_view hostname, string_view type);

    private:
        uint16_t id;

        auto buildMessage(string_view hostname, string_view type) -> void;
        [[nodiscard]] static auto getTypeIDFromString(string_view type) -> uint16_t;
    };

    struct InvalidQuestionType : public std::runtime_error {
        InvalidQuestionType() :
            std::runtime_error(
                "The DNS record type you requested is invalid or not supported."
            ) {}
    };
} // namespace Dns

#endif // DNS_LOOKUP_DNS_QUESTION_H
