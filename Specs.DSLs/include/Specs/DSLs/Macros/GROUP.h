#pragma once

#include <Specs/GlobalSpecGroup.h>

#include "MacrosCore.h"  // IWYU pragma: keep

#define __SPEC_GROUP_BODY(symbol, specGroupDescription, count)                                    \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)();      \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(symbol, count){[]( \
                                                                                              ) { \
        SpecsCpp::DSLs::GlobalInterface::register_group_fn(                                       \
            specGroupDescription,                                                                 \
            _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)             \
        );                                                                                        \
    }};                                                                                           \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)()

#define _SPEC_GROUP(symbol, specGroupDescription) \
    __SPEC_GROUP_BODY(symbol, specGroupDescription, __COUNTER__)
