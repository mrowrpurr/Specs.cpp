#pragma once

#include <functional>

namespace Spec::Internal {

    //! Lazy way to run arbitrary function on startup by providing a function.
    struct FunctionRunner {
        FunctionRunner(std::function<void()> fn) { fn(); }
    };
}
