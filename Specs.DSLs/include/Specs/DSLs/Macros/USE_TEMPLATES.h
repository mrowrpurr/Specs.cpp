#pragma once

#include <Specs/GlobalSpecGroup.h>

#include "MacrosCore.h"  // IWYU pragma: keep

#define _SPEC_USE_TEMPLATES(...)                                                        \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME(_SPEC_USE_TEMPLATE_ \
    ){[]() { SpecsCpp::GlobalSpecGroup::instance().use_templates({__VA_ARGS__}); }};
