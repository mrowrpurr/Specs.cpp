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

_GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME(_SPEC_GROUP_FROM_SPEC_FILE_){[]() {
    SpecsCpp::GlobalSpecGroup::instance().declare_file_group(
        _GLOBAL_MACRO_FUNCTIONS_STRINGIZE(spec_name)
    );
}};

#elif defined(spec_template)
    #define _GLOBAL_MACRO_FUNCTIONS_COMPILATION_UNIT_NAME spec_template

    #include <Specs/GlobalSpecGroup.h>
    #include <global_macro_functions.h>

_GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME(_SPEC_GROUP_FROM_SPEC_FILE_){[]() {
    SpecsCpp::GlobalSpecGroup::instance().declare_top_level_template(
        _GLOBAL_MACRO_FUNCTIONS_STRINGIZE(spec_template), true
    );
}};

#endif

#include <global_macro_functions.h>
