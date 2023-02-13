#pragma once

#include "Spec/Internal/Macros/Core.h"
#include "Spec/Internal/Macros/FunctionRunner.h"

#define __Spec_Macro_Register_Describe(description, count)                                                       \
    inline void __Spec_Macro_Unique(count)();                                                                    \
    __Spec_Macro_FunctionRunner(count){[]() {                                                                    \
        ::Spec::SpecContext::GetDefault().GetDiscovery().DiscoverGroup(description, __Spec_Macro_Unique(count)); \
    }};                                                                                                          \
    inline void __Spec_Macro_Unique(count)

#define Describe(description) __Spec_Macro_Register_Describe(description, __COUNTER__)()
