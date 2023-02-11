#pragma once

#include <functional>

#include "Spec/SpecController.h"


#define __SPEC_MACRO_CONCAT0(x, y) x##y
#define __SPEC_MACRO_CONCAT(x, y) __SPEC_MACRO_CONCAT0(x, y)

// Create a "FunctionRunner" which takes a std::function which is run immediately at runtime
#define __SPEC_MACRO_FUNCTIONRUNNER(count) \
    Spec::Internal::FunctionRunner __SPEC_MACRO_CONCAT(__specGroupDefinition, count)

// Setup for a callback function to be registered, e.g. as a SystemEvent handler
#define __SPEC_MACRO_CALLBACKFN_NAME(count) \
    __SPEC_MACRO_CONCAT(__skyrimScriptingPluginCallback, count)

// Add a System Event Callback to SKSEPlugin
//
// It'll call the function which the developer defines using the macro
// so they need access to the same __COUNTER__ (which is why we take the count as an argument)
//
#define __SPEC_MACRO_REGISTER_AND_DEFINE_CALLBACK(count)                         \
    inline void __SPEC_MACRO_CALLBACKFN_NAME(count)();                           \
    __SPEC_MACRO_FUNCTIONRUNNER(count){[]() {                                    \
        Spec::SpecController::GetSingleton()._RegisterSpecBlockToEvaluate([]() { \
            __SPEC_MACRO_CALLBACKFN_NAME(count)();                               \
        });                                                                      \
    }};                                                                          \
    inline void __SPEC_MACRO_CALLBACKFN_NAME(count)

#define Specs __SPEC_MACRO_REGISTER_AND_DEFINE_CALLBACK(__COUNTER__)()

namespace Spec::Internal {
    //! Lazy way to run arbitrary function on startup by providing a function.
    struct FunctionRunner {
        FunctionRunner(std::function<void()> fn) { fn(); }
    };
}

// Useful!
// #define __NEW_SPEC_MACRO_FUNCTIONRUNNER __SPEC_MACRO_FUNCTIONRUNNER(__COUNTER__)
// #define SomeMacro(someArg)                                       \
//     __NEW_SPEC_MACRO_FUNCTIONRUNNER {                        \
//         []() { SkyrimScripting::Plugin::Config::LogFullPath = fullPath; } \
//     }