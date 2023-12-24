#pragma once

#include <Specs/GlobalSpecGroup.h>
#include <Specs/SpecDataValue.h>

#include "MacrosCore.h"  // IWYU pragma: keep

#define _SPEC_TAG(tagName)                                                     \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME(_SPEC_TAG_ \
    ){[]() { SpecsCpp::GlobalSpecGroup::instance().add_tag_for_next_component(tagName); }};
