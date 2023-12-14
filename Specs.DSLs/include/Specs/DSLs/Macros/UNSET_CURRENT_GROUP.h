#pragma once

#include <Specs/GlobalSpecGroup.h>

#include "MacrosCore.h"  // IWYU pragma: keep

#define _SPEC_UNSET_CURRENT_GROUP(symbol)                                  \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME(symbol \
    ){[]() { SpecsCpp::GlobalSpecGroup::instance().clear_top_level_group(); }};
