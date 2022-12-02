// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <iostream>

#include "dns/name.h"

namespace Dns {
    Name::Name(const char* data) {
        generateLabelsWithData(data);
    }

    // TODO: modify this class
    void Name::generateLabelsWithData(const char* p) {
        if (!*p) return; 
        const int len = *p++;
        std::string label {""};
        for (int i = 0; i < len; ++i) label += *p++;
        labels.emplace_back(label);
        generateLabelsWithData(p);
    }

    int Name::getSize() const {
        auto size = 0;
        for (const auto& label : labels) {
            size += label.size();
        }
        return size + static_cast<int>(labels.size()) + 1;
    }

    std::string Name::getName() const {
        std::string output {};
        for (const auto& label : labels) {
            output += static_cast<char>(size(label));
            output += label;
        }
        output += '\0';
        return output;
    }

    std::string Name::getHostname() const {
        std::string output {};
        for (const auto& label : labels) {
            output += label;
            output += ".";
        }
        return output.substr(0, output.size() - 1);
    }
}