#pragma once

#include <Specs/GlobalSpecGroup.h>
#include <Specs/SpecDone.h>

#include "MacrosCore.h"  // IWYU pragma: keep

#define __SPEC_ASYNC_TEST_BODY(symbol, specDescription, count)                                    \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)(        \
        SpecsCpp::ISpec*, SpecsCpp::SpecDone                                                      \
    );                                                                                            \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(symbol, count){[]( \
                                                                                              ) { \
        SpecsCpp::DSLs::GlobalInterface::define_test_fn(                                          \
            specDescription,                                                                      \
            _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)             \
        );                                                                                        \
    }};                                                                                           \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)(        \
        [[maybe_unused]] SpecsCpp::ISpec * current_spec, SpecsCpp::SpecDone done                  \
    )

#define _SPEC_ASYNC_TEST(specDescription) \
    __SPEC_ASYNC_TEST_BODY(_SPEC_ASYNC_TEST_, specDescription, __COUNTER__)
