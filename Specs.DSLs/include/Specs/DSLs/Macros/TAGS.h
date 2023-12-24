#pragma once

#include <Specs/GlobalSpecGroup.h>
#include <Specs/SpecDataValue.h>

#include "MacrosCore.h"  // IWYU pragma: keep

#define _SPEC_TAGS(...)                                                         \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME(_SPEC_TAGS_ \
    ){[]() { SpecsCpp::GlobalSpecGroup::instance().add_tags_for_next_component({__VA_ARGS__}); }};
