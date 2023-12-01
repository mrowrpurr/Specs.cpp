#pragma once

#include <Specs/GlobalSpecGroup.h>

#include <functional>

inline void describe(std::string_view description, std::function<void()> body) {
    SpecsCpp::GlobalSpecGroup::instance().register_group_fn(
        description, function_pointer(std::move(body))
    );
}
