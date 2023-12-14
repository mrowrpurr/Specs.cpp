#pragma once

#include <Specs/GlobalSpecCodeBlocks.h>

#include "MacrosCore.h"  // IWYU pragma: keep

#define _SPEC_CODE_BLOCK(symbol) \
    _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_NAMED_FUNCTION(                         \
        symbol, SpecsCpp::GlobalSpecCodeBlocks::instance().register_code_block \
    )()
