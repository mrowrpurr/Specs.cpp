#pragma once

#include "../Macros/DECLARE_TEMPLATE.h"
#include "../Macros/SAVE_CURRENT_GROUP_STACK.h"

#define StartTestTemplate(templateName)   \
    _SPEC_SAVE_GROUP_STACK();             \
    _SPEC_DECLARE_TEMPLATE(templateName); \
    namespace
