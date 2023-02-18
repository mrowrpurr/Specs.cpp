#pragma once

#include "Spec/Internal/Macros/Core.h"
#include "Spec/Internal/Macros/FunctionRunner.h"

#define __Spec_Macro_Register_Setup(count)                                                             \
    inline void __Spec_Macro_Unique(count)();                                                          \
    __Spec_Macro_FunctionRunner(count){[]() {                                                          \
        Spec::Types::SpecDefinitionBlocks::GetGlobalInstance().RegisterBlock([]() {                    \
            Spec::Types::SpecDiscovery::GetGlobalInstance().DiscoverSetup(__Spec_Macro_Unique(count)); \
        });                                                                                            \
    }};                                                                                                \
    inline void __Spec_Macro_Unique(count)()

#define Setup __Spec_Macro_Register_Setup(__COUNTER__)
