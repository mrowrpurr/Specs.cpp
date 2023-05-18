#pragma once

#include <string_format.h>

#include <algorithm>
#include <iostream>

#include "../ISpecReporter.h"
#include "Utilities/PrintColor.h"

namespace Specs::Reporters {

    //! `Specs.cpp` reporter which prints out a single line per test case.
    class OneLineReporter : public ISpecReporter {
        std::string removeTrailingNewline(const std::string& text) {
            std::string str{text};
            if (!str.empty() && str[str.size() - 1] == '\n') str.erase(str.size() - 1);
            return str;
        }

        void PrintPassed(const std::string& testDescription) {
            Utilities::PrintColor(string_format("PASS: {}\n", testDescription), Utilities::Colors::Color::Green);
        }
        void PrintFailed(const std::string& testDescription, const std::string& failureMessage) {
            if (!failureMessage.empty())
                Utilities::PrintColor(
                    string_format("FAIL: {} ({})\n", testDescription, removeTrailingNewline(failureMessage)),
                    Utilities::Colors::Color::Red
                );
            else
                Utilities::PrintColor(string_format("FAIL: {}\n", testDescription), Utilities::Colors::Color::Red);
        }
        void PrintNotRun(const std::string& testDescription) {
            Utilities::PrintColor(string_format("NOT RUN: {}\n", testDescription), Utilities::Colors::Color::Yellow);
        }

    public:
        void BeginTestCase(std::shared_ptr<SpecTestCase> testCase) override {}

        void EndTestCase(std::shared_ptr<SpecTestCase> testCase, SpecTestCaseResult testResult) override {
            if (testResult.Passed()) {
                PrintPassed(testCase->GetFullDescription());
            } else if (testResult.Failed()) {
                PrintFailed(testCase->GetFullDescription(), testResult.GetFailureMessage());
            } else {
                PrintNotRun(testCase->GetFullDescription());
            }
        }

        void BeginTestGroup(std::shared_ptr<SpecTestGroup> testGroup) override {}
        void EndTestGroup(std::shared_ptr<SpecTestGroup> testGroup) override {}
    };
}