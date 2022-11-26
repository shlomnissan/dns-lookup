// Copyright 2022 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef DNS_LOOKUP_EXCEPTIONS_H
#define DNS_LOOKUP_EXCEPTIONS_H

#include <exception>

namespace Common {
    struct InvalidQuestionType : public std::exception {
        const char* what() const throw() {
            return "The DNS record type you requested is invalid.";
        }
    };

    struct InvalidHostnameLength : public std::exception {
        const char* what() const throw() {
            return "The hostname you entered exceeds the limit of 255 characters.";
        }
    };

    struct BufferOutOfRange : public std::exception {
        const char* what() const throw() {
            return "The message buffer is out of range.";
        }
    };
};

#endif  // DNS_LOOKUP_EXCEPTIONS_H