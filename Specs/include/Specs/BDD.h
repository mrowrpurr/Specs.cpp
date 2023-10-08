#pragma once

#include "CLI.h"
#include "DSL/BDD.h"

namespace Specs {

    void BDD(const CLI& cli) {
        auto app      = cli.GetApplication();
        auto registry = app->GetRegistry();
        Specs::SpecGlobalScope::Get().SetGlobalGroup(registry->GetRootTestGroup());
        Specs::SpecGlobalScope::Get().SetTestDescriptionSeparator(" > ");
    }
}
