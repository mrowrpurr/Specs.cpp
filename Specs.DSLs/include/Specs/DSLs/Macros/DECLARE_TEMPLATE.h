#pragma once

#include <Specs/GlobalSpecGroup.h>

#include "MacrosCore.h"  // IWYU pragma: keep

#define _SPEC_DECLARE_TEMPLATE(templateName)                                                \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME(_SPEC_DECLARE_TEMPLATE_ \
    ){[]() { SpecsCpp::GlobalSpecGroup::instance().declare_top_level_template(templateName); }};
