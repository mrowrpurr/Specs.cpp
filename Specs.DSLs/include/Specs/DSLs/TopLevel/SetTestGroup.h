#pragma once

#include "../Internal/Macros.h"

#define SetTestGroup(description) \
    _SPEC_MACRO_DEFINE_TOP_LEVEL_GROUP(_SetTestGroupDSLMacro_, description)
