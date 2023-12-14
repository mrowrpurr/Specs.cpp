#pragma once

#include <Specs/GlobalSpecGroup.h>
#include <Specs/SpecDone.h>

#include "MacrosCore.h"  // IWYU pragma: keep

#define __SPEC_ASYNC_SETUP_BODY(symbol, count)                                                    \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)(        \
        SpecsCpp::ISpecGroup*, SpecsCpp::ISpecComponent*, SpecsCpp::ISpec*, SpecsCpp::SpecDone    \
    );                                                                                            \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(symbol, count){[]( \
                                                                                              ) { \
        SpecsCpp::DSLs::GlobalInterface::register_setup_fn(                                       \
            _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)             \
        );                                                                                        \
    }};                                                                                           \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)(        \
        SpecsCpp::ISpecGroup * current_group, SpecsCpp::ISpecComponent * current_setup,           \
        SpecsCpp::ISpec * current_spec, SpecsCpp::SpecDone done                                   \
    )

#define _SPEC_ASYNC_SETUP(symbol) __SPEC_ASYNC_SETUP_BODY(symbol, __COUNTER__)
