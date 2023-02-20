#pragma once

#include <memory>

#include "Specs/SpecTestCaseRun.h"
#include "Specs/SpecTestGroup.h"

namespace Specs {

    //! Interface for reporters. Provides callbacks for reporting test results.
    class ISpecReporter {
    public:
        //! Called when a test case is starting.
        virtual void BeginTestCase(std::shared_ptr<SpecTestCaseRun> testCaseRun) = 0;

        //! Called when a test case is ending.
        virtual void EndTestCase(std::shared_ptr<SpecTestCaseRun> testCaseRun) = 0;

        //! Called when a test group is starting.
        virtual void BeginTestGroup(std::shared_ptr<SpecTestGroup> testGroup) = 0;

        //! Called when a test group is ending.
        virtual void EndTestGroup(std::shared_ptr<SpecTestGroup> testGroup) = 0;
    };
}
