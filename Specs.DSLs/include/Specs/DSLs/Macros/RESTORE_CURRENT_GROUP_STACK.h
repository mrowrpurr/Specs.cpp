#pragma once

#include <Specs/GlobalSpecGroup.h>

#include "MacrosCore.h"  // IWYU pragma: keep

#define _SPEC_RESTORE_GROUP_STACK()                                                            \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME(_SPEC_RESTORE_GROUP_STACK_ \
    ){[]() { SpecsCpp::GlobalSpecGroup::instance().restore_group_stack(); }};
