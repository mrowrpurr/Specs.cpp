#pragma once

#include "Spec/Internal/Macros/Core.h"
#include "Spec/Internal/SpecController.h"

#define __Spec_Macro_Register_RootTest(description, count)                                     \
    inline void __Spec_Macro_UniqueVariableName(count)();                                      \
    __Spec_Macro_FunctionRunner(count){[]() {                                                  \
        Spec::Internal::SpecController::GetSingleton().DefineSpecTest(description, [](auto&) { \
            __Spec_Macro_UniqueVariableName(count)();                                          \
        });                                                                                    \
    }};                                                                                        \
    inline void __Spec_Macro_UniqueVariableName(count)

#define Test(description) __Spec_Macro_Register_RootTest(description, __COUNTER__)()
