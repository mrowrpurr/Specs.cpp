#pragma once

#include <string_format.h>

#include <iostream>

#include "../ISpecReporter.h"
#include "Utilities/PrintColor.h"

namespace Spec::Types::Reporters {

    class OneLineReporter : public ISpecReporter {
        void PrintPassed(const std::string& testDescription) {
            Utilities::PrintColor(string_format("PASS: {}", testDescription), Utilities::Colors::Color::Green);
        }
        void PrintFailed(const std::string& testDescription, const std::string& failureMessage) {
            if (!failureMessage.empty())
                Utilities::PrintColor(
                    string_format("FAIL: {} ({})", testDescription, failureMessage), Utilities::Colors::Color::Red
                );
            else
                Utilities::PrintColor(string_format("FAIL: {}", testDescription), Utilities::Colors::Color::Red);
        }
        void PrintNotRun(const std::string& testDescription) {
            Utilities::PrintColor(string_format("NOT RUN: {}", testDescription), Utilities::Colors::Color::Yellow);
        }

    public:
        void BeginTest(std::shared_ptr<SpecTest>, SpecTestResult&) override {}
        void EndTest(std::shared_ptr<SpecTest> test, SpecTestResult& result) override {
            if (result.Passed()) {
                PrintPassed(test->GetFullDescription());
            } else if (result.Failed()) {
                PrintFailed(test->GetFullDescription(), result.GetFailureMessageWithFileLocation());
            } else {
                PrintNotRun(test->GetFullDescription());
            }
        }
        void BeginSetup(std::shared_ptr<SpecTest>, SpecTestResult&) override {}
        void EndSetup(std::shared_ptr<SpecTest>, SpecTestResult&) override {}
        void BeginTeardown(std::shared_ptr<SpecTest>, SpecTestResult&) override {}
        void EndTeardown(std::shared_ptr<SpecTest>, SpecTestResult&) override {}
        void BeginGroup(SpecGroup&, SpecGroupResult&) override {}
        void EndGroup(SpecGroup&, SpecGroupResult&) override {}
    };
}
