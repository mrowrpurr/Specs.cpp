#pragma once

#include <future>
#include <memory>

namespace Specs {

    //! Represents the run of a single test case, connecing SpecTestCase to SpecTestCaseResult.
    class SpecTestCaseRun {
        std::shared_ptr<std::promise<void>> _testCompletionPromise;

    public:
        //! Returns the promise which should be fulfilled when the test case completes.
        std::shared_ptr<std::promise<void>> GetTestCompletionPromise() { return _testCompletionPromise; }
    };
}
