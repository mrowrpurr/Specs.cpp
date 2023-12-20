#pragma once

#include <Specs/GlobalSpecGroup.h>
#include <Specs/SpecDone.h>

#include <functional>

#include "../GlobalInterface.h"

namespace SpecsCpp::DSLs::Functions {

    inline void setup(std::function<void()> body) {
        SpecsCpp::DSLs::GlobalInterface::define_setup_fn(function_pointer(std::move(body)));
    }

    inline void setup(std::function<void(SpecsCpp::SpecDone)> body) {
        SpecsCpp::DSLs::GlobalInterface::define_setup_fn(function_pointer(std::move(body)));
    }
}
