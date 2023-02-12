#pragma once

#include "Spec/Internal/Macros/Core.h"
#include "Spec/Internal/SpecController.h"

#define __Spec_Macro_Register_RootSpecsBlock(count)                                         \
    inline void __Spec_Macro_UniqueVariableName(count)();                                   \
    __Spec_Macro_FunctionRunner(count){[]() { __Spec_Macro_UniqueVariableName(count)(); }}; \
    inline void __Spec_Macro_UniqueVariableName(count)

#define Specs __Spec_Macro_Register_RootSpecsBlock(__COUNTER__)()
