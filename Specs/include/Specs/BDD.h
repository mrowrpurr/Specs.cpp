#pragma once

#include "CLI.h"
#include "DSL/Components/Functions/DefineTest.h"
#include "DSL/Components/Functions/DefineTestGroup.h"

constexpr auto DefineTest = [](auto&&... args) {
    Specs::DSL::Components::Functions::DefineTest(std::forward<decltype(args)>(args)...);
};
constexpr auto DefineTestGroup = [](auto&&... args) {
    Specs::DSL::Components::Functions::DefineTestGroup(std::forward<decltype(args)>(args)...);
};

const auto it       = DefineTest;
const auto describe = DefineTestGroup;

namespace Specs {

    void BDD(const CLI& cli) {
        auto app      = cli.GetApplication();
        auto registry = app->GetRegistry();
        Specs::SpecGlobalScope::Get().SetGlobalGroup(registry->GetRootTestGroup());
        Specs::SpecGlobalScope::Get().SetTestDescriptionSeparator(" > ");
    }
}
