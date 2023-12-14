#pragma once

// Before including <global_macro_functions.h>
#if defined(spec_context)
    #define _GLOBAL_MACRO_FUNCTIONS_COMPILATION_UNIT_NAME spec_context
#elif defined(spec_file)
    #define _GLOBAL_MACRO_FUNCTIONS_COMPILATION_UNIT_NAME spec_file
#elif defined(spec_name)
    #define _GLOBAL_MACRO_FUNCTIONS_COMPILATION_UNIT_NAME spec_name
#endif

#include <global_macro_functions.h>
