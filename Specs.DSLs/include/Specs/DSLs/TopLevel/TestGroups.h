#pragma once

#include "../Macros/DECLARE_GROUPS.h"

#define TestGroups(topLevelGroup, ...) _SPEC_DECLARE_GROUPS(topLevelGroup, __VA_ARGS__)
