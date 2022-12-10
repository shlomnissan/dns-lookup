// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_NAME_H
#define DNS_LOOKUP_NAME_H

#include <string>
#include <vector>

#include "network/buffer.h"

namespace Dns {
    using Network::Buffer;
    using std::string;
    using std::string_view;
    using std::vector;

    class Name {
    public:
        Name() = default;

        auto initWithData(const Buffer& message, const char* p) -> void;
        auto initWithHostname(string_view hostname) -> void;

        [[nodiscard]] auto getSize() const -> int { return size; }
        [[nodiscard]] auto getName() const -> string { return name; };
        [[nodiscard]] auto getHostname() const -> string { return hostname; };

    private:
        int size = 0;
        string name {};
        string hostname {};
        vector<std::string> labels {};

        auto processLabels() -> void;
        auto isCompressionLabel(const char* p) const -> bool;
        auto getCompressionLabelAddress(const char* p) const -> uint16_t;
    };
} // namespace Dns

#endif // DNS_LOOKUP_NAME_H