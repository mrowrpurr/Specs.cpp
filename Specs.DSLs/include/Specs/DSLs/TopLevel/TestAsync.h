#pragma once

#include "../Internal/Macros.h"

#define TestAsync(description) \
    _SPEC_MACRO_FUNCTIONS_REGISTER_GLOBAL_ASYNC_SPEC(_TestAsyncDSLMacro_, description)
