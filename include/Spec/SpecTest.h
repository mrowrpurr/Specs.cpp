#pragma once

#include <functional>
#include <future>
#include <optional>

namespace Spec {

    struct SpecTest {
        std::string                         description;
        std::shared_ptr<std::promise<bool>> promisePtr;
        std::function<void(SpecTest&)>      body;
    };
}