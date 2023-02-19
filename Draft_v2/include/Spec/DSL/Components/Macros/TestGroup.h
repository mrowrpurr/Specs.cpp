#pragma once

#include "Spec/Internal/Macros/Core.h"
#include "Spec/Internal/Macros/FunctionRunner.h"

#define __Spec_Macro_Register_TestGroup(description, count)                                 \
    __Spec_Macro_FunctionRunner(count) {                                                    \
        []() {                                                                              \
            Spec::Types::SpecDefinitionBlocks::GetGlobalInstance().RegisterBlock([]() {     \
                Spec::Types::SpecDiscovery::GetGlobalInstance().DiscoverGroup(description); \
            });                                                                             \
        }                                                                                   \
    }

#define TestGroup(description) __Spec_Macro_Register_TestGroup(description, __COUNTER__)
