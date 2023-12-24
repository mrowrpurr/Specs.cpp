#pragma once

#include <Specs/GlobalSpecGroup.h>
#include <Specs/SpecDone.h>

#include "MacrosCore.h"  // IWYU pragma: keep

#define _SPEC_ASYNC_TEARDOWN_BODY(symbol, count)                                                  \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)(        \
        SpecsCpp::ISpecGroup*, SpecsCpp::ISpecComponent*, SpecsCpp::ISpec*, SpecsCpp::SpecDone    \
    );                                                                                            \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(symbol, count){[]( \
                                                                                              ) { \
        SpecsCpp::DSLs::GlobalInterface::define_teardown_fn(                                      \
            _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)             \
        );                                                                                        \
    }};                                                                                           \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)(        \
        [[maybe_unused]] SpecsCpp::ISpecGroup * current_group,                                    \
        [[maybe_unused]] SpecsCpp::ISpecComponent * current_teardown,                             \
        [[maybe_unused]] SpecsCpp::ISpec * current_test, SpecsCpp::SpecDone done                  \
    )

#define _SPEC_ASYNC_TEARDOWN() _SPEC_ASYNC_TEARDOWN_BODY(_SPEC_ASYNC_TEARDOWN_, __COUNTER__)
