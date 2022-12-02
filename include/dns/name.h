// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_NAME_H
#define DNS_LOOKUP_NAME_H

#include <vector>
#include <string>

namespace Dns {
    class Name {
    public:
        explicit Name(const char* data);

        [[nodiscard]] int getSize() const; 
        [[nodiscard]] std::string getName() const;
        [[nodiscard]] std::string getHostname() const;
    private:
        std::vector<std::string> labels {};
        
        void generateLabelsWithData(const char* data);
    };
}

#endif  // DNS_LOOKUP_NAME_H 