#pragma once

#include <Specs/GlobalSpecGroup.h>

#include "MacrosCore.h"  // IWYU pragma: keep

#define __SPEC_ONE_TIME_SETUP_BODY(symbol, count)                                                                                                      \
    inline void                                                                                                                                        \
        _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)(SpecsCpp::ISpecGroup*, SpecsCpp::ISpecComponent*, SpecsCpp::ISpec*); \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(symbol, count){[](                                                      \
                                                                                              ) {                                                      \
        SpecsCpp::DSLs::GlobalInterface::define_one_time_setup_fn(                                                                                     \
            _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)                                                                  \
        );                                                                                                                                             \
    }};                                                                                                                                                \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)(                                                             \
        SpecsCpp::ISpecGroup * current_group, SpecsCpp::ISpecComponent * current_setup,                                                                \
        SpecsCpp::ISpec * current_spec                                                                                                                 \
    )

#define _SPEC_ONE_TIME_SETUP() __SPEC_ONE_TIME_SETUP_BODY(_SPEC_ONE_TIME_SETUP_, __COUNTER__)
