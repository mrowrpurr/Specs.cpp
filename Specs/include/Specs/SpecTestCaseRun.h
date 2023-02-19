#pragma once

#include <future>
#include <memory>

#include "Specs/SpecTestCaseResult.h"

namespace Specs {

    //! Represents the run of a single test case, connecing SpecTestCase to SpecTestCaseResult.
    class SpecTestCaseRun {
        std::shared_ptr<std::promise<void>> _testCompletionPromise;
        std::shared_ptr<SpecTestCaseResult> _result;

    public:
        //! Returns the result of the test case.
        std::shared_ptr<SpecTestCaseResult> GetResult() { return _result; }

        //! Returns the promise which should be fulfilled when the test case completes.
        std::shared_ptr<std::promise<void>> GetTestCompletionPromise() { return _testCompletionPromise; }
    };
}
