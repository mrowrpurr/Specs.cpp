#pragma once

#include "Components/Functions/DefineTest.h"
#include "Components/Functions/DefineTestGroup.h"

#define it(...) Specs::DSL::Components::Functions::DefineTest(__VA_ARGS__)
#define describe(...) Specs::DSL::Components::Functions::DefineTestGroup(__VA_ARGS__)
