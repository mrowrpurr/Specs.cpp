#pragma once

#include <Specs/GlobalSpecGroup.h>
#include <Specs/SpecDone.h>

#include <functional>

inline void setup(std::function<void()> body) {
    SpecsCpp::GlobalSpecGroup::instance().register_setup_fn(function_pointer(std::move(body)));
}

inline void setup(std::function<void(SpecsCpp::SpecDone)> body) {
    SpecsCpp::GlobalSpecGroup::instance().register_setup_fn(function_pointer(std::move(body)));
}
