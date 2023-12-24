#pragma once

#include "../Macros/GROUP_REMOVE_UNDERSCORES.h"

#define DescribeFn(symbol) __SPEC_GROUP_REMOVE_UNDERSCORES_BODY(symbol, #symbol, __COUNTER__)