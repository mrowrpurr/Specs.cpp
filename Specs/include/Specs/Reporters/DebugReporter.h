#pragma once

#include "Specs/ISpecReporter.h"

//! Test reporters.
namespace Specs::Reporters {

    //! `Specs.cpp` reporter that prints detailed output (useful for debugging `Specs.cpp`).
    class DebugReporter : public ISpecReporter {
        void BeginTestCase(std::shared_ptr<SpecTestCase> testCase) override {
            Print("[DEBUG] BEGIN TEST CASE: " + testCase->GetFullDescription());
        }

        void EndTestCase(std::shared_ptr<SpecTestCase> testCase, SpecTestCaseResult testResult) override {
            Print("[DEBUG] END TEST CASE: " + testCase->GetFullDescription());
            Print("[DEBUG] TEST CASE RESULT: " + testResult.GetFailureMessage());
        }

        void BeginTestGroup(std::shared_ptr<SpecTestGroup> testGroup) override {
            Print("[DEBUG] BEGIN TEST GROUP: " + testGroup->GetFullDescription());
        }

        void EndTestGroup(std::shared_ptr<SpecTestGroup> testGroup) override {
            Print("[DEBUG] END TEST GROUP: " + testGroup->GetFullDescription());
        }
    };
}