// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <iostream>
#include <sstream>

#include "dns/name.h"

namespace Dns {
    void Name::initWithData(const Buffer& message, const char* p) {
        if (*p == 0x00) {
            processLabels();
            return;
        }
        if (isCompressionLabel(p)) {
            auto addr = getCompressionLabelAddress(p);
            return initWithData(message, message.getData() + addr);
        } else {
            const int len = *p++;
            std::string label {p, p + len};
            labels.emplace_back(label);
            initWithData(message, p + label.size());
        }
    }

    void Name::initWithHostname(std::string_view host) {
        std::stringstream ss {host.data()};
        std::string label {};
        while (getline(ss, label, '.')) {
            labels.emplace_back(label);
        }
        processLabels();
    }

    void Name::processLabels() {
        for (const auto& label : labels) {
            name += static_cast<char>(label.size()) + label;
            hostname += "." + label;
        }
        name += '\0';
        size = static_cast<int>(name.size());
        hostname = hostname.substr(1);
    }

    bool Name::isCompressionLabel(const char* p) const {
        return (*p & 0xC0 /* = 11000000*/) == 0xC0;
    }

    uint16_t Name::getCompressionLabelAddress(const char* p) const {
        return ((*p & 0x3F /* = 00111111 */) << 8) | p[1];
    }
} // namespace Dns