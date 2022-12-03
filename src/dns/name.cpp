// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <sstream>

#include "dns/name.h"

namespace Dns {
    void Name::initWithData(const char* p) {
        if (!*p) {
            processLabels();
            return;
        }
        const int len = *p++;
        std::string label {};
        for (int i = 0; i < len; ++i) label += *p++;
        labels.emplace_back(label);
        initWithData(p);
    }

    void Name::initWithHostname(std::string_view host) {
        std::stringstream ss { host.data() };
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
}