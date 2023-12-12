#pragma once

#include "../Internal/Macros.h"

#define Configure(configureContextToken) \
    _SPEC_MACRO_FUNCTIONS_REGISTER_GLOBAL_CODE_BLOCK(configureContextToken)
