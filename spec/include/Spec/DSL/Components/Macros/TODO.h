#pragma once

#include "Spec/Internal/Macros/Core.h"
#include "Spec/Internal/Macros/FunctionRunner.h"

#define __Spec_Macro_Register_TODO(description, count)                                     \
    __Spec_Macro_FunctionRunner(count) {                                                   \
        []() {                                                                             \
            Spec::Types::SpecDefinitionBlocks::GetGlobalInstance().RegisterBlock([]() {    \
                Spec::Types::SpecDiscovery::GetGlobalInstance().DiscoverTest(description); \
            });                                                                            \
        }                                                                                  \
    }

#define TODO(description) __Spec_Macro_Register_TODO(description, __COUNTER__)
