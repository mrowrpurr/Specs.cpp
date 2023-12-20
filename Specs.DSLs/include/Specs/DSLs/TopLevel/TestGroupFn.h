#pragma once

#include "../Macros/GROUP.h"

#define TestGroupFn(token) __SPEC_GROUP_BODY(token, #token, __COUNTER__)
