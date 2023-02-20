#pragma once

#include <future>
#include <memory>

#include "Specs/SpecTestCase.h"

namespace Specs {

    //! Represents the run of a single test case, connecing SpecTestCase to SpecTestCaseResult.
    class SpecTestCaseRun {
        std::shared_ptr<std::promise<void>> _testCompletionPromise;
        std::shared_ptr<SpecTestCase>       _testCase;

    public:
        //! Creates a new test case run.
        SpecTestCaseRun(std::shared_ptr<SpecTestCase> testCase) : _testCase(testCase) {
            _testCompletionPromise = std::make_shared<std::promise<void>>();
        }

        //! Returns the promise which should be fulfilled when the test case completes.
        std::shared_ptr<std::promise<void>> GetTestCompletionPromise() { return _testCompletionPromise; }

        //! Returns the test case.
        std::shared_ptr<SpecTestCase> GetTestCase() { return _testCase; }
    };
}
