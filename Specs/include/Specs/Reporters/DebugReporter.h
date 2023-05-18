#pragma once

#include <iostream>

#include "../ISpecReporter.h"

//! Test reporters.
namespace Specs::Reporters {

    //! `Specs.cpp` reporter that prints detailed output (useful for debugging `Specs.cpp`).
    class DebugReporter : public ISpecReporter {
        void BeginTestCase(std::shared_ptr<SpecTestCase> testCase) override {
            std::cout << "[DEBUG] BEGIN TEST CASE: " + testCase->GetFullDescription() << std::endl;
        }

        void EndTestCase(std::shared_ptr<SpecTestCase> testCase, SpecTestCaseResult testResult) override {
            std::cout << "[DEBUG] END TEST CASE: " + testCase->GetFullDescription() << std::endl;
            std::cout << "[DEBUG] TEST CASE RESULT: " + testResult.GetFailureMessage() << std::endl;
        }

        void BeginTestGroup(std::shared_ptr<SpecTestGroup> testGroup) override {
            std::cout << "[DEBUG] BEGIN TEST GROUP: " + testGroup->GetFullDescription() << std::endl;
        }

        void EndTestGroup(std::shared_ptr<SpecTestGroup> testGroup) override {
            std::cout << "[DEBUG] END TEST GROUP: " + testGroup->GetFullDescription() << std::endl;
        }
    };
}