#pragma once

#include "Spec/Internal/Macros/Core.h"
#include "Spec/Internal/Macros/FunctionRunner.h"

#define __Spec_Macro_Specs(count)                                               \
    inline void __Spec_Macro_Unique(count)();                                   \
    __Spec_Macro_FunctionRunner(count){[]() { __Spec_Macro_Unique(count)(); }}; \
    inline void __Spec_Macro_Unique(count)

#define Specs __Spec_Macro_Specs(__COUNTER__)()
