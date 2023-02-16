#pragma once

#include "Spec/Internal/Macros/Core.h"
#include "Spec/Internal/Macros/FunctionRunner.h"

#define __Spec_Macro_Register_Test(description, count)                                                             \
    inline void __Spec_Macro_Unique(count)();                                                                      \
    __Spec_Macro_FunctionRunner(count){[]() {                                                                      \
        Spec::Types::SpecDefinitionBlocks::GetGlobalInstance().RegisterBlock([]() {                                \
            Spec::Types::SpecDiscovery::GetGlobalInstance().DiscoverTest(description, __Spec_Macro_Unique(count)); \
        });                                                                                                        \
    }};                                                                                                            \
    inline void __Spec_Macro_Unique(count)

#define Test(description) __Spec_Macro_Register_Test(description, __COUNTER__)()
