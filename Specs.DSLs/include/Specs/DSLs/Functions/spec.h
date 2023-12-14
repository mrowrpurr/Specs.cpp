#pragma once

#include <Specs/GlobalSpecGroup.h>
#include <Specs/SpecDone.h>

#include <functional>

#include "../GlobalInterface.h"

namespace SpecsCpp::DSLs::Functions {

    inline void spec(std::string_view description, std::function<void()> body) {
        SpecsCpp::DSLs::GlobalInterface::register_spec_fn(
            description, function_pointer(std::move(body))
        );
    }

    inline void spec(std::string_view description, std::function<void(SpecsCpp::SpecDone)> body) {
        SpecsCpp::DSLs::GlobalInterface::register_spec_fn(
            description, function_pointer(std::move(body))
        );
    }
}
