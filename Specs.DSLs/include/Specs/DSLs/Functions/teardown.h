#pragma once

#include <Specs/GlobalSpecGroup.h>
#include <Specs/SpecDone.h>

#include <functional>

#include "../GlobalInterface.h"

namespace SpecsCpp::DSLs::Functions {

    inline void teardown(std::function<void()> body) {
        SpecsCpp::DSLs::GlobalInterface::define_teardown_fn(function_pointer(std::move(body)));
    }

    inline void teardown(std::function<void(SpecsCpp::SpecDone)> body) {
        SpecsCpp::DSLs::GlobalInterface::define_teardown_fn(function_pointer(std::move(body)));
    }
}
