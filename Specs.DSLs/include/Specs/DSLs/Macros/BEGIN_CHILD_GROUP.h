#pragma once

#include <Specs/GlobalSpecGroup.h>

#include "MacrosCore.h"  // IWYU pragma: keep

#define _SPEC_BEGIN_CHILD_GROUP(description)                                                 \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME(_SPEC_BEGIN_CHILD_GROUP_ \
    ){[]() { SpecsCpp::GlobalSpecGroup::instance().declare_group(description); }};
