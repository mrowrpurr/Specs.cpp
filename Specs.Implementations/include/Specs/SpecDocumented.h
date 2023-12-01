#pragma once

#include <Specs/API.h>

#include <string>
#include <string_view>

namespace SpecsCpp {

    class SpecDocumented : public virtual ISpecDocumented {
        std::string _description;

    public:
        SpecDocumented(std::string_view description) : _description(description) {}

        const char* description() const override { return _description.c_str(); }
    };
}
