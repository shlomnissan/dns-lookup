// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <cstdint>
#include <iostream>
#include <sstream>

#include "dns/name.h"

namespace Dns {
    auto Name::initWithData(const Buffer& message, const char* p) -> void {
        if (*p == 0x00) {
            processLabels();
            return;
        }
        if (isCompressionLabel(p)) {
            compression_label_count++;
            auto addr = getCompressionLabelAddress(p);
            initWithData(message, message.data() + addr);
        } else {
            const int len = *p++;
            string label {p, p + len};
            labels.emplace_back(label);
            initWithData(message, p + label.size());
        }
    }

    auto Name::initWithHostname(string_view host) -> void {
        std::stringstream ss {host.data()};
        string label {};
        while (getline(ss, label, '.')) {
            labels.emplace_back(label);
        }
        processLabels();
    }

    auto Name::getSize() const -> int {
        return compression_label_count ? compression_label_count * 2 : size;
    }

    auto Name::processLabels() -> void {
        for (const auto& label : labels) {
            name += static_cast<char>(label.size()) + label;
            hostname += "." + label;
        }
        name += '\0';
        size = static_cast<int>(name.size());
        hostname = hostname.substr(1);
    }

    auto Name::isCompressionLabel(const char* p) const -> bool {
        return (*p & 0xC0 /* = 11000000*/) == 0xC0;
    }

    auto Name::getCompressionLabelAddress(const char* p) const -> uint16_t {
        return ((*p & 0x3F /* = 00111111 */) << 8) | p[1];
    }
} // namespace Dns