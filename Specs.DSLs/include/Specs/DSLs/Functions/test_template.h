#pragma once

#include <Specs/GlobalSpecGroup.h>

#include <functional>

#include "../GlobalInterface.h"

namespace SpecsCpp::DSLs::Functions {

    inline void test_template(std::string_view templateName, std::function<void()> body) {
        SpecsCpp::DSLs::GlobalInterface::register_template_fn(
            templateName, function_pointer(std::move(body))
        );
    }
}
