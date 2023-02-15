#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Spec/SpecTest.h"

namespace Spec {

    //! Represents a collection of child SpecTest and other SpecGroup.
    struct SpecGroup {
        std::string            description;
        std::vector<SpecTest>  setups;
        std::vector<SpecTest>  teardowns;
        std::vector<SpecTest>  tests;
        std::vector<SpecGroup> groups;
    };
}
