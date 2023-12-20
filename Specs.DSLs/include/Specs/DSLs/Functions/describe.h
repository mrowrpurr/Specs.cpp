#pragma once

#include <functional>

#include "../GlobalInterface.h"

namespace SpecsCpp::DSLs::Functions {

    inline void describe(std::string_view description, std::function<void()> body) {
        SpecsCpp::DSLs::GlobalInterface::define_group_fn(
            description, function_pointer(std::move(body))
        );
    }
}
