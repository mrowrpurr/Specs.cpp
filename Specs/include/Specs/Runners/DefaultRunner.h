#pragma once

#include <queue>

#include "Specs/ISpecRunner.h"

//! Test runners.
namespace Specs::Runners {

    //! `Specs.cpp` default test runner (see also ParallelSpecRunner).
    class DefaultRunner : public ISpecRunner {
        std::queue<std::shared_ptr<SpecTestCase>>           _testCaseQueue;
        std::shared_ptr<SpecTestGroupResult>                _results;
        std::vector<std::shared_ptr<ISpecReporter>>         _reporters;
        std::vector<std::shared_ptr<ISpecExceptionHandler>> _exceptionHandlers;
        RunnerOptions                                       _runnerOptions;
        ReporterOptions                                     _reporterOptions;

        void LoadQueue(std::shared_ptr<SpecTestGroup> testGroup) {
            for (auto& test : testGroup->GetTestCases()) _testCaseQueue.push(test);
            for (auto& group : testGroup->GetTestGroups()) LoadQueue(group);
        }

    public:
        //! Runs the specified tests and returns a future that will be set when the tests are complete.
        std::promise<void> RunSpecs(
            std::shared_ptr<SpecTestGroup> tests, std::shared_ptr<SpecTestGroupResult> results,
            std::vector<std::shared_ptr<ISpecReporter>>         reporters,
            std::vector<std::shared_ptr<ISpecExceptionHandler>> exceptionHandlers, RunnerOptions runnerOptions,
            ReporterOptions reporterOptions
        ) override {
            LoadQueue(tests);

            // Print out the tests
            while (!_testCaseQueue.empty()) {
                auto testCase = _testCaseQueue.front();
                _testCaseQueue.pop();

                Print("[TEST]: {}", testCase->GetFullDescription());
            }

            std::promise<void> promise;
            promise.set_value();
            return promise;
        }
    };
}
