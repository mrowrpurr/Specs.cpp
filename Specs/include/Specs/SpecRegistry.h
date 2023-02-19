#pragma once

#include <memory>

#include "Specs/SpecTestCase.h"
#include "Specs/SpecTestGroup.h"

namespace Specs {

    //! Provides helper functions for registering test cases and groups in SpecTestGroup.
    class SpecRegistry {
        std::shared_ptr<SpecTestGroup> _tests;

    public:
        explicit SpecRegistry(std::shared_ptr<SpecTestGroup> tests) : _tests(tests) {}
    };
}