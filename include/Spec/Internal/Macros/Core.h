#pragma once

#include <functional>

// Helper macros
#define __SPEC_MACRO_CONCAT_(x, y) x##y
#define __SPEC_MACRO_CONCAT(x, y) __SPEC_MACRO_CONCAT_(x, y)

namespace Spec::Internal {
    //! Lazy way to run arbitrary function on startup by providing a function.
    struct FunctionRunner {
        FunctionRunner(std::function<void()> fn) { fn(); }
    };
}

// Create a "FunctionRunner" which takes a std::function which is run immediately at runtime
#define __Spec_Macro_FunctionRunner(count) \
    Spec::Internal::FunctionRunner __SPEC_MACRO_CONCAT(__specGroupDefinition, count)

#define __Spec_Macro_UniqueVariableName(count) __SPEC_MACRO_CONCAT(__spec_macro_variable__, count)
