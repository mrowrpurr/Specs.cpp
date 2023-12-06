#pragma once

#include "Components/Functions/DefineTest.h"       // IWYU pragma: keep
#include "Components/Functions/DefineTestGroup.h"  // IWYU pragma: keep

#define it(...) Specs::DSL::Components::Functions::DefineTest(__VA_ARGS__)
#define describe(...) Specs::DSL::Components::Functions::DefineTestGroup(__VA_ARGS__)

#define xit(...)
#define xdescribe(...)
