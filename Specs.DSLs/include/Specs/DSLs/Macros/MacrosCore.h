#pragma once

// Before including <global_macro_functions.h>

#if defined(spec_context)
    #define _GLOBAL_MACRO_FUNCTIONS_COMPILATION_UNIT_NAME spec_context

#elif defined(spec_file)
    #define _GLOBAL_MACRO_FUNCTIONS_COMPILATION_UNIT_NAME spec_file

#elif defined(spec_name)
    #define _GLOBAL_MACRO_FUNCTIONS_COMPILATION_UNIT_NAME spec_name

    #include <Specs/GlobalSpecGroup.h>
    #include <global_macro_functions.h>

    #define _SPECS_CORE_STRINGIZE_CORE(symbol) #symbol
    #define _SPECS_CORE_STRINGIZE(symbol) _SPECS_CORE_STRINGIZE_CORE(symbol)

// clang-format off
_GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME(_SPEC_GROUP_FROM_SPEC_FILE_){[](){ SpecsCpp::GlobalSpecGroup::instance().register_top_level_group(_SPECS_CORE_STRINGIZE(spec_name)); }};
// clang-format on

#endif

#include <global_macro_functions.h>
