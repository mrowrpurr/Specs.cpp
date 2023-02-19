#pragma once

#include "Spec/Internal/FunctionRunner.h"
#include "Spec/Internal/Macros/Core.h"


// Create a "FunctionRunner" which takes a std::function which is run immediately at runtime
#define __Spec_Macro_FunctionRunner(count) \
    Spec::Internal::FunctionRunner __Spec_Macro_Concat(__specGroupDefinition, count)
