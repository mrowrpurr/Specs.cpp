#pragma once

#include <Specs/GlobalSpecGroup.h>

#include "MacrosCore.h"  // IWYU pragma: keep

#define _SPEC_RESET_CURRENT_GROUP_STACK()                                                      \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME(_SPEC_UNSET_CURRENT_GROUP_ \
    ){[]() { SpecsCpp::GlobalSpecGroup::instance().reset_group_stack(); }};
