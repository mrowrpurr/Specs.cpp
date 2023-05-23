#pragma once

#include <functional>
#include <string>

#include "Specs/SpecRegistry.h"
#include "Specs/SpecTestGroup.h"

namespace Specs::DSL::Components::Functions {

    //! Defines and registers a test group.
    inline std::shared_ptr<SpecTestGroup> DefineTestGroup(const std::string& description, std::function<void()> body) {
        return SpecRegistry::GlobalRegistry().RegisterTestGroup(description, body);
    }
}
