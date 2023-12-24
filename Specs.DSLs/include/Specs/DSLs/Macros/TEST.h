#pragma once

#include <Specs/GlobalSpecGroup.h>

#include "MacrosCore.h"  // IWYU pragma: keep

#define _SPEC_TEST_BODY(symbol, specDescription, count)                                                                     \
    inline void                                                                                                             \
        _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)(SpecsCpp::ISpecGroup*, SpecsCpp::ISpec*); \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(symbol, count){[](                           \
                                                                                              ) {                           \
        SpecsCpp::DSLs::GlobalInterface::define_test_fn(                                                                    \
            specDescription,                                                                                                \
            _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)                                       \
        );                                                                                                                  \
    }};                                                                                                                     \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)(                                  \
        [[maybe_unused]] SpecsCpp::ISpecGroup * current_group,                                                              \
        [[maybe_unused]] SpecsCpp::ISpec * current_test                                                                     \
    )

#define _SPEC_TEST(specDescription) _SPEC_TEST_BODY(_SPEC_TEST_, specDescription, __COUNTER__)
