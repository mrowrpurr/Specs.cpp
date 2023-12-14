#pragma once

#include "../Macros/TEMPLATE.h"

#define TestTemplateFn(symbol) __SPEC_TEMPLATE_BODY(symbol, #symbol, __COUNTER__)
