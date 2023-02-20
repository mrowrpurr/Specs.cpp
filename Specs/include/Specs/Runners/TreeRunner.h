#pragma once

#include "Specs/ISpecRunner.h"

namespace Specs::Runners {

    class TreeRunner : public ISpecRunner {
        std::promise<void> RunSpecs(
            std::shared_ptr<SpecTestGroup> tests, std::vector<std::shared_ptr<ISpecReporter>> reporters,
            std::vector<std::shared_ptr<ISpecExceptionHandler>> exceptionHandlers, RunnerOptions runnerOptions,
            ReporterOptions reporterOptions
        ) override {
            std::promise<void> promise;
            return promise;
        };
    };
}
