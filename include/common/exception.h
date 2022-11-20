// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_EXCEPTIONS_H
#define DNS_LOOKUP_EXCEPTIONS_H

#include <exception>

namespace Common {
    struct InvalidQuestionType : public std::exception {
        const char* what() const throw() {
            return "The DNS record type you entered is invalid. Use a, mx, txt, aaaa, or any instead.";
        }
    };

    struct InvalidHostnameLength : public std::exception {
        const char* what() const throw() {
            return "The hostname your entered is too long.";
        }
    };
};

#endif  // DNS_LOOKUP_EXCEPTIONS_H