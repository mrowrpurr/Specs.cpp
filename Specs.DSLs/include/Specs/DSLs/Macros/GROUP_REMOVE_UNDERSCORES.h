#pragma once

#include <Specs/GlobalSpecGroup.h>

#include "MacrosCore.h"  // IWYU pragma: keep

#define __SPEC_GROUP_REMOVE_UNDERSCORES_BODY(symbol, specGroupDescription, count)                   \
    inline void                                                                                     \
        _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)(SpecsCpp::        \
                                                                                      ISpecGroup*); \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(symbol, count){[](   \
                                                                                              ) {   \
        SpecsCpp::DSLs::GlobalInterface::define_group_fn(                                           \
            specGroupDescription,                                                                   \
            _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count), true         \
        );                                                                                          \
    }};                                                                                             \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)(          \
        [[maybe_unused]] SpecsCpp::ISpecGroup * current_group                                       \
    )

#define _SPEC_GROUP_REMOVE_UNDERSCORES(specGroupDescription) \
    __SPEC_GROUP_REMOVE_UNDERSCORES_BODY(_SPEC_GROUP_, specGroupDescription, __COUNTER__)
