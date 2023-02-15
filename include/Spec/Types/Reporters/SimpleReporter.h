#pragma once

#include <iostream>

#include "Spec/Types/ISpecReporter.h"

namespace Spec::Types::Reporters {

    class SimpleReporter : public ISpecReporter {
    public:
        void BeginTest(SpecTest&) override {}
        void EndTest(SpecTest& test, bool passed, const std::string& failureMessage) override {
            if (passed)
                std::cout << "PASS: " << test.GetDescription() << std::endl;
            else
                std::cout << "FAIL: " << test.GetDescription() << "\n" << failureMessage << std::endl;
        }
        void BeginGroup(SpecGroup& group) override {
            if (group.GetDescription() != "") std::cout << std::format("[{}]", group.GetDescription()) << std::endl;
        }
        void EndGroup(SpecGroup&) override {}
    };
}
