#pragma once

#include <functional>
#include <future>
#include <string>

namespace Spec {

    struct SpecTest {
        std::string                    description;
        std::promise<bool>             promise = {};
        std::function<void(SpecTest&)> body;
    };
}