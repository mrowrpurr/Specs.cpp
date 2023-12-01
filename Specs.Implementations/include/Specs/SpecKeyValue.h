#pragma once

#include <Specs/API.h>

#include <string>
#include <string_view>

namespace SpecsCpp {

    class SpecKeyValue : public ISpecKeyValue {
        std::string _key;
        std::string _value;

    public:
        SpecKeyValue(std::string_view key, std::string_view value) : _key(key), _value(value) {}

        const char* key() const override { return _key.c_str(); }
        const char* value() const override { return _value.c_str(); }
    };
}
