#pragma once

#include <queue>

#include "Specs/ISpecRunner.h"
#include "Specs/SpecTestCase.h"
#include "Specs/SpecTestCaseRun.h"

//! Test runners.
namespace Specs::Runners {

    //! `Specs.cpp` default test runner (see also ParallelSpecRunner).
    class DefaultRunner : public ISpecRunner {
        std::mutex                                          _popTestCaseFromQueueMutex;
        std::queue<std::shared_ptr<SpecTestCase>>           _testCaseQueue;
        std::vector<std::shared_ptr<ISpecReporter>>         _reporters;
        std::vector<std::shared_ptr<ISpecExceptionHandler>> _exceptionHandlers;
        RunnerOptions                                       _runnerOptions;
        ReporterOptions                                     _reporterOptions;

        void LoadQueue(std::shared_ptr<SpecTestGroup> testGroup) {
            for (auto& test : testGroup->GetTestCases()) _testCaseQueue.push(test);
            for (auto& group : testGroup->GetTestGroups()) LoadQueue(group);
        }

        void RunTestCase(std::shared_ptr<SpecTestCase> testCase) {
            Print("Running test case: " + testCase->GetFullDescription());

            // Setup the test case run
            auto testCaseRun = std::make_shared<SpecTestCaseRun>(testCase);

            // Inform the reporters that the test case is starting
            for (auto& reporter : _reporters) reporter->BeginTestCase(testCaseRun);

            // Replace with exception handling...
            // testCase->Run(testCaseRun);

            // Inform the reporters that the test case is ending
            for (auto& reporter : _reporters) reporter->EndTestCase(testCaseRun);
        }

        void RunNextTestCase() {
            std::shared_ptr<SpecTestCase> testCase;
            {
                std::lock_guard<std::mutex> lock(_popTestCaseFromQueueMutex);
                if (_testCaseQueue.empty()) return;
                testCase = _testCaseQueue.front();
                _testCaseQueue.pop();
            }
            RunTestCase(testCase);
        }

        //! Runs all of the tests in the queue.
        void RunTests() {
            Print("Running tests...");
            while (!_testCaseQueue.empty()) RunNextTestCase();
        }

    public:
        //! Runs the specified tests and returns a future that will be set when the tests are complete.
        std::promise<void> RunSpecs(
            std::shared_ptr<SpecTestGroup> tests, std::vector<std::shared_ptr<ISpecReporter>> reporters,
            std::vector<std::shared_ptr<ISpecExceptionHandler>> exceptionHandlers, RunnerOptions runnerOptions,
            ReporterOptions reporterOptions
        ) override {
            _reporters         = reporters;
            _exceptionHandlers = exceptionHandlers;

            Print("Loading test cases...");
            LoadQueue(tests);
            Print("Running test cases...");
            std::promise<void> promise;
            RunTests();
            promise.set_value();
            return promise;
        }
    };
}
