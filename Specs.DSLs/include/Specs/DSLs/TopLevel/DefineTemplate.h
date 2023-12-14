#pragma once

#include "../Internal/Macros.h"

#define DefineTemplate(templateName) \
    _SPEC_MACRO_DEFINE_TOP_LEVEL_TEMPLATE(_DefineTemplateDSLMacro_, templateName)
