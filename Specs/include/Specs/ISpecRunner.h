#pragma once

#include <future>
#include <queue>

#include "ISpecExceptionHandler.h"
#include "ISpecReporter.h"
#include "ReporterOptions.h"
#include "RunnerOptions.h"
#include "SpecTestGroup.h"

namespace Specs {

    //! Interface for test suite runners which run SpecTestGroup.
    class ISpecRunner {
    public:
        //! Runs the specified tests and returns a future that will be set when the tests are complete.
        virtual std::promise<void> RunSpecs(
            std::shared_ptr<SpecTestGroup> tests, std::vector<std::shared_ptr<ISpecReporter>> reporters,
            std::vector<std::shared_ptr<ISpecExceptionHandler>> exceptionHandlers, RunnerOptions runnerOptions,
            ReporterOptions reporterOptions
        ) = 0;
    };
}
