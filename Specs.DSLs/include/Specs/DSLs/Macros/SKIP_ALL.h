#pragma once

#include <Specs/GlobalSpecGroup.h>
#include <Specs/SpecDataValue.h>

#include "MacrosCore.h"  // IWYU pragma: keep

#define _SPEC_SKIP_ALL()                                                               \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME(_SPEC_SKIP_ALL_) { \
        []() {                                                                         \
            if (auto* currentGroup = SpecsCpp::GlobalSpecGroup::instance().get())      \
                currentGroup->mark_skipped(true);                                      \
        }                                                                              \
    }
