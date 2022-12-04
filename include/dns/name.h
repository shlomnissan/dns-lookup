// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_NAME_H
#define DNS_LOOKUP_NAME_H

#include <vector>
#include <string>

#include "common/buffer.h"

namespace Dns {
    using namespace Common;

    class Name {
    public:
        Name() = default;

        void initWithData(const Buffer& message, const char* p);
        void initWithHostname(std::string_view hostname);

        [[nodiscard]] int getSize() const { return size; } 
        [[nodiscard]] std::string getName() const { return name; };
        [[nodiscard]] std::string getHostname() const { return hostname; };
    private:
        int size = 0;
        std::string name {};
        std::string hostname {};
        std::vector<std::string> labels {};
        
        void processLabels();
        bool isCompressionLabel(const char* p) const;
        uint16_t getCompressionLabelAddress(const char* p) const;
    };
}

#endif  // DNS_LOOKUP_NAME_H 