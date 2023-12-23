#pragma once

#include "../Macros/BEGIN_CHILD_GROUP.h"

#define StartTestGroup(description)       \
    _SPEC_BEGIN_CHILD_GROUP(description); \
    namespace
