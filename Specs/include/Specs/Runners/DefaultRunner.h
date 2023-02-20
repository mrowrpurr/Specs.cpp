#pragma once

#include "Specs/ISpecRunner.h"

//! Test runners.
namespace Specs::Runners {

    //! `Specs.cpp` default test runner (see also ParallelSpecRunner).
    class DefaultRunner : public ISpecRunner {
    public:
        //! Runs the specified tests and returns a future that will be set when the tests are complete.
        std::promise<void> RunSpecs(
            std::shared_ptr<SpecTestGroup> tests, std::shared_ptr<SpecTestGroupResult> results,
            std::vector<std::shared_ptr<ISpecReporter>>         reporters,
            std::vector<std::shared_ptr<ISpecExceptionHandler>> exceptionHandlers, RunnerOptions runnerOptions,
            ReporterOptions reporterOptions
        ) override {
            std::promise<void> promise;
            return promise;
        }
    };
}
