#pragma once

#include <format>
#include <iostream>

#include "Spec/SpecGroup.h"

namespace Spec {

    class SpecRunner {
    public:
        void RunGroup(SpecGroup& group) {
            std::cout << "Run group!" << std::endl;
            std::cout << std::format("There are {} tests in this group", group.tests.size())
                      << std::endl;
            std::cout << std::format("There are {} CHILD GROUPS in this group", group.groups.size())
                      << std::endl;
            for (auto& test : group.tests) {
                // run setups

                // run test
                std::cout << std::format("Gonna run test: {}", test.description) << std::endl;
                // run teardowns

                //
                test.body(test);
            }
        }
    };
}
