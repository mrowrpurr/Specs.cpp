#pragma once

#include "Specs/SpecTestCase.h"
#include "Specs/SpecTestCaseRun.h"

namespace Specs {

    //! Used a parameter for SpecTestCase body functions. Wraps SpecTestCase and SpecTestCaseRun
    /**
     * Test cases can accept this parameter as a parameter to their body function.
     *
     * It provides the primary API for interacting with the test case from within the test case body.
     *
     * Notes:
     * - SpecTestCaseRun represents this individual run of the test case.
     * - SpecTestCase represents the test case itself.
     *
     * The test promise and result are stored in the SpecTestCaseRun.
     */
    class SpecTestCaseParam {
        std::shared_ptr<SpecTestCase>    _test;
        std::shared_ptr<SpecTestCaseRun> _run;
    };
}
