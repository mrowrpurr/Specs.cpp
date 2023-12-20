#pragma once

#include <Specs/SpecDone.h>

#include <functional>

#include "../GlobalInterface.h"

namespace SpecsCpp::DSLs::Functions {

    inline void it(std::string_view description, std::function<void()> body) {
        SpecsCpp::DSLs::GlobalInterface::define_test_fn(
            description, function_pointer(std::move(body))
        );
    }

    inline void it(std::string_view description, std::function<void(SpecsCpp::SpecDone)> body) {
        SpecsCpp::DSLs::GlobalInterface::define_test_fn(
            description, function_pointer(std::move(body))
        );
    }
}
