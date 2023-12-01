#pragma once

#include <Specs/GlobalSpecGroup.h>
#include <Specs/SpecDone.h>

#include <functional>

inline void teardown(std::function<void()> body) {
    SpecsCpp::GlobalSpecGroup::instance().register_teardown_fn(function_pointer(std::move(body)));
}

inline void teardown(std::function<void(SpecsCpp::SpecDone)> body) {
    SpecsCpp::GlobalSpecGroup::instance().register_teardown_fn(function_pointer(std::move(body)));
}
