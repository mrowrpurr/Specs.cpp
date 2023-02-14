#pragma once

#include <format>
#include <iostream>

#include "Spec/SpecReporter.h"


namespace Spec::Reporters {

    class SimpleReporter : public SpecReporter {
    public:
        void BeginTest(SpecTest&) override {}
        void EndTest(SpecTest& test, bool passed, const std::string& failureMessage) override {
            if (passed)
                std::cout << "PASS: " << test.description << std::endl;
            else
                std::cout << "FAIL: " << test.description << "\n" << failureMessage << std::endl;
        }
        void BeginGroup(SpecGroup& group) override {
            if (group.description != "") std::cout << std::format("[{}]", group.description) << std::endl;
        }
        void EndGroup(SpecGroup&) override {}
    };
}
