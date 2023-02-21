#pragma once

#include <functional>
#include <string>

#include "Specs/SpecRegistry.h"
#include "Specs/SpecTestCase.h"


namespace Specs::DSL::Components::Functions {

    //! Defines and registers a test.
    std::shared_ptr<SpecTestCase> DefineTest(
        const std::string& description, std::function<void(std::shared_ptr<SpecTestCaseParam>)> block
    ) {
        return SpecRegistry::GlobalRegistry().RegisterTestCase(description, block);
    }
}
