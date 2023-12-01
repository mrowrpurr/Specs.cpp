#pragma once

#include "../Internal/Macros.h"

#define Describe(description) \
    _SPEC_MACRO_FUNCTIONS_REGISTER_GLOBAL_SPEC_GROUP(_SpecDSLMacro_, description)
