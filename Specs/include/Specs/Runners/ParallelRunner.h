#pragma once

#include "../ISpecRunner.h"

namespace Specs::Runners {

    //! `Specs.cpp` test runner that runs tests in parallel (see also SpecRunner).
    class ParallelRunner : public ISpecRunner {
    public:
        //! Runs the specified tests and returns a future that will be set when the tests are complete.
        std::promise<void> RunSpecs(
            std::shared_ptr<SpecTestGroup> tests, std::vector<std::shared_ptr<ISpecReporter>> reporters,
            std::vector<std::shared_ptr<ISpecExceptionHandler>> exceptionHandlers, RunnerOptions runnerOptions,
            ReporterOptions reporterOptions
        ) override {
            std::promise<void> promise;
            return promise;
        }
    };
}
