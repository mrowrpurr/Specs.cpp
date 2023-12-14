#pragma once

#include <Specs/GlobalSpecGroup.h>
#include <Specs/SpecDone.h>

#include <functional>

inline void test(std::string_view description, std::function<void()> body) {
    SpecsCpp::GlobalSpecGroup::instance().register_spec_fn(
        description, function_pointer(std::move(body))
    );
}

inline void test(std::string_view description, std::function<void(SpecsCpp::SpecDone)> body) {
    SpecsCpp::GlobalSpecGroup::instance().register_spec_fn(
        description, function_pointer(std::move(body))
    );
}

inline void test(std::string_view description, std::function<void(SpecsCpp::ISpecGroup*)> body) {
    SpecsCpp::GlobalSpecGroup::instance().register_spec_fn(
        description, function_pointer(std::move(body))
    );
}
