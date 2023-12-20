#pragma once

#include <Specs/GlobalSpecCodeBlocks.h>

#include "MacrosCore.h"  // IWYU pragma: keep

#define _SPEC_CODE_BLOCK() \
    _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_NAMED_FUNCTION(                         \
        _SPEC_CODE_BLOCK_, SpecsCpp::GlobalSpecCodeBlocks::instance().register_code_block \
    )()
