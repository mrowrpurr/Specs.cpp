#pragma once

#include <Specs/GlobalSpecGroup.h>

#include "MacrosCore.h"  // IWYU pragma: keep

#define _SPEC_TEMPLATE(templateNameSymbol)                                                     \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME(templateNameSymbol){[]() { \
        SpecsCpp::GlobalSpecGroup::instance().declare_top_level_template(#templateNameSymbol); \
    }};
