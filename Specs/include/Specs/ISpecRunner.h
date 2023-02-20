#pragma once

#include <future>
#include <queue>

#include "Specs/ISpecExceptionHandler.h"
#include "Specs/ISpecReporter.h"
#include "Specs/ReporterOptions.h"
#include "Specs/RunnerOptions.h"
#include "Specs/SpecTestGroup.h"

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
