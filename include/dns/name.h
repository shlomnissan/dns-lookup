// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_NAME_H
#define DNS_LOOKUP_NAME_H

#include <vector>
#include <string>

namespace Dns {
    class Name {
    public:
        Name() = default;

        void initWithData(const char* p);
        void initWithHostname(std::string_view hostname);

        [[nodiscard]] int getSize() const { return size; } 
        [[nodiscard]] std::string getName() const { return name; };
        [[nodiscard]] std::string getHostname() const { return hostname; };
    private:
        int size = 0;
        std::string name {};
        std::string hostname {};
        std::vector<std::string> labels {};
        
        void generateLabelsWithData(const char* data);
        void processLabels();
    };
}

#endif  // DNS_LOOKUP_NAME_H 