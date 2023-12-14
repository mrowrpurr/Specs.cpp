#pragma once

#include "../Macros/MacrosCore.h"  // IWYU pragma: keep

#define ConfigureFn(token) \
    _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_NAMED_FUNCTION(                         \
        token, SpecsCpp::GlobalSpecCodeBlocks::instance().register_code_block \
    )()
