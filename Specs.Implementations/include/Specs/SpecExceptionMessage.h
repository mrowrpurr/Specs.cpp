#pragma once

#include <Specs/API.h>

#include <string>
#include <string_view>

namespace SpecsCpp {

    class SpecExceptionMessage : public ILocalSpecExceptionHandler::IExceptionMessage {
        std::string _message;

    public:
        SpecExceptionMessage(std::string_view message) : _message(message) {}

        const char* message() const override { return _message.c_str(); }
    };
}
