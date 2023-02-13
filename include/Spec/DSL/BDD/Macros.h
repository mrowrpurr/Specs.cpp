#pragma once

#include "Spec/Internal/Macros/Core.h"
#include "Spec/Internal/Macros/FunctionRunner.h"
#include "Spec/SpecContext.h"

/** Specs { } */

#define __Spec_Macro_Specs(count)                                               \
    inline void __Spec_Macro_Unique(count)();                                   \
    __Spec_Macro_FunctionRunner(count){[]() { __Spec_Macro_Unique(count)(); }}; \
    inline void __Spec_Macro_Unique(count)

#define Specs __Spec_Macro_Specs(__COUNTER__)()

/** Describe { } */

#define __Spec_Macro_Register_Describe(description, count)              \
    inline void __Spec_Macro_Unique(count)();                           \
    __Spec_Macro_FunctionRunner(count){[]() {                           \
        ::Spec::SpecContext::GetDefault().GetDiscovery().DiscoverGroup( \
            description, __Spec_Macro_Unique(count)                     \
        );                                                              \
    }};                                                                 \
    inline void __Spec_Macro_Unique(count)

#define Describe(description) __Spec_Macro_Register_Describe(description, __COUNTER__)()

/** Test { } */

#define __Spec_Macro_Register_Test(description, count)                 \
    inline void __Spec_Macro_Unique(count)();                          \
    __Spec_Macro_FunctionRunner(count){[]() {                          \
        ::Spec::SpecContext::GetDefault().GetDiscovery().DiscoverTest( \
            description, __Spec_Macro_Unique(count)                    \
        );                                                             \
    }};                                                                \
    inline void __Spec_Macro_Unique(count)

#define Test(description) __Spec_Macro_Register_Test(description, __COUNTER__)()
