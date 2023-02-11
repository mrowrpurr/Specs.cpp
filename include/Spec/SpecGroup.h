#pragma once

#include <string>
#include <vector>

#include "Spec/SpecTest.h"

namespace Spec {

    //! Represents a colletion of one or more Spec (tests)
    struct SpecGroup {
        std::string            description;
        std::vector<SpecTest>  setups;
        std::vector<SpecTest>  teardowns;
        std::vector<SpecTest>  tests;
        std::vector<SpecGroup> groups;
    };
}
