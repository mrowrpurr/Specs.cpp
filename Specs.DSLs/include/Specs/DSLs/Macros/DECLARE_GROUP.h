#pragma once

#include <Specs/GlobalSpecGroup.h>

#include "MacrosCore.h"  // IWYU pragma: keep

#define _SPEC_DECLARE_GROUP(symbol, description)                           \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME(symbol \
    ){[]() { SpecsCpp::GlobalSpecGroup::instance().register_top_level_group(description); }};
