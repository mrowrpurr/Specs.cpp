#pragma once

#include <Specs/GlobalSpecGroup.h>

#include <functional>

inline void test_template(std::string_view templateName, std::function<void()> body) {
    SpecsCpp::GlobalSpecGroup::instance().register_template_fn(
        templateName, function_pointer(std::move(body))
    );
}
