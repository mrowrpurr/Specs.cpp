#pragma once

#include <Specs/GlobalSpecGroup.h>

#include "MacrosCore.h"  // IWYU pragma: keep

#define __SPEC_ONE_TIME_TEARDOWN_BODY(symbol, count)                                                                                                   \
    inline void                                                                                                                                        \
        _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)(SpecsCpp::ISpecGroup*, SpecsCpp::ISpecComponent*, SpecsCpp::ISpec*); \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(symbol, count){[](                                                      \
                                                                                              ) {                                                      \
        SpecsCpp::DSLs::GlobalInterface::define_one_time_teardown_fn(                                                                                  \
            _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)                                                                  \
        );                                                                                                                                             \
    }};                                                                                                                                                \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)(                                                             \
        [[maybe_unused]] SpecsCpp::ISpecGroup * current_group,                                                                                         \
        [[maybe_unused]] SpecsCpp::ISpecComponent * current_teardown,                                                                                  \
        [[maybe_unused]] SpecsCpp::ISpec * current_test                                                                                                \
    )

#define _SPEC_ONE_TIME_TEARDOWN() \
    __SPEC_ONE_TIME_TEARDOWN_BODY(_SPEC_ONE_TIME_TEARDOWN_, __COUNTER__)
