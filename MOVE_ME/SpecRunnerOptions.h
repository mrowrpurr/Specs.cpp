#pragma once

#include <functional>
#include <string>

namespace Spec {

    // TODO
    struct SpecRunnerOptions {
        bool                             parallel    = false;
        bool                             randomOrder = false;
        std::function<bool(std::string)> specFilter;
    };
}