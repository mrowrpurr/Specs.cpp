#pragma once

#include "../Internal/Macros.h"

#define TestTemplate(templateName) \
    _SPEC_MACRO_FUNCTIONS_DEFINE_TEMPLATE(_TestTemplateDSLMacro_, templateName)
