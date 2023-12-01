#pragma once

#include "../Internal/Macros.h"

#define SpecAsync(description) \
    _SPEC_MACRO_FUNCTIONS_REGISTER_GLOBAL_ASYNC_SPEC(_SpecAsyncDSLMacro_, description)
