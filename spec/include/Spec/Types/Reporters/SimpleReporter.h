#pragma once

#include <iostream>

#include "Spec/Types/ISpecReporter.h"

namespace Spec::Types::Reporters {

    class SimpleReporter : public ISpecReporter {
    public:
        void BeginTest(std::shared_ptr<SpecTest> test, SpecTestResult&) override {}
        void EndTest(std::shared_ptr<SpecTest> test, SpecTestResult& result) override {
            if (result.Passed()) {
                std::cout << std::format("    [{}] {}", result.Passed() ? "PASS" : "FAIL", test.GetDescription())
                          << std::endl;
            } else {
                std::cout << std::format("    [{}] {}", result.Passed() ? "PASS" : "FAIL", test.GetDescription())
                          << std::endl;
                std::cout << std::format("        {}", result.GetFailureMessageWithFileLocation()) << std::endl;
            }
        }
        void BeginGroup(SpecGroup& group, SpecGroupResult&) override {
            if (group.GetDescription() != "") std::cout << std::format("[{}]", group.GetDescription()) << std::endl;
        }
        void EndGroup(SpecGroup&, SpecGroupResult&) override {}
    };
}
