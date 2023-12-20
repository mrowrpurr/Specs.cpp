#pragma once

#include <Specs.h>
#include <Specs/LibAssert.h>
#include <Specs/Snowhouse.h>

BeginTestTemplate("SpecHelper Template");

Setup {
    _Log_("Hi from SpecHelper setup " _GLOBAL_MACRO_FUNCTIONS_STRINGIZE(
        _GLOBAL_MACRO_FUNCTIONS_COMPILATION_UNIT_NAME
    ));
}

EndTestTemplate();
