#pragma once

#include <Specs/GlobalSpecGroup.h>

#include "MacrosCore.h"  // IWYU pragma: keep

#define _SPEC_UNSET_CURRENT_GROUP()                                                            \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME(_SPEC_UNSET_CURRENT_GROUP_ \
    ){[]() { SpecsCpp::GlobalSpecGroup::instance().clear_top_level_group(); }};
