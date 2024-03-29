#pragma once

#include <Specs/GlobalSpecGroup.h>
#include <Specs/SpecDone.h>

#include <functional>

#include "../GlobalInterface.h"

namespace SpecsCpp::DSLs::Functions {

    inline void test(std::string_view description, std::function<void()> body) {
        SpecsCpp::DSLs::GlobalInterface::define_test_fn(
            description, function_pointer(std::move(body))
        );
    }

    inline void test(std::string_view description, std::function<void(SpecsCpp::SpecDone)> body) {
        SpecsCpp::DSLs::GlobalInterface::define_test_fn(
            description, function_pointer(std::move(body))
        );
    }

    inline void test(
        std::string_view description, std::function<void(SpecsCpp::ISpecGroup*)> body
    ) {
        SpecsCpp::DSLs::GlobalInterface::define_test_fn(
            description, function_pointer(std::move(body))
        );
    }
}
