#pragma once

#include <iostream>

#include "Spec/Types/ISpecReporter.h"

namespace Spec::Types::Reporters {

    class OneLineReporter : public ISpecReporter {
    public:
        void BeginTest(SpecTest&) override {}
        void EndTest(SpecTest& test, bool passed, const std::string& failureMessage) override {
            std::string testDescription = test.GetDescription();
            auto        group           = test.GetGroup();
            while (group) {
                testDescription = group->GetDescription() + " " + testDescription;
                group           = group->GetParent();
            }
            if (!failureMessage.empty()) {
                std::cout << (passed ? "PASS" : "FAIL") << ": " << testDescription << " (" << failureMessage << ")"
                          << std::endl;
            } else {
                std::cout << (passed ? "PASS" : "FAIL") << ": " << testDescription << std::endl;
            }
        }
        void BeginGroup(SpecGroup& group) override {}
        void EndGroup(SpecGroup&) override {}
    };
}
