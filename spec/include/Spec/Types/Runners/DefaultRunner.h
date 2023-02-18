#pragma once

#include <format>
#include <memory>
#include <stacktrace>

#include "Spec/Types/ISpecRunner.h"
#include "Spec/Types/SpecExtensionsRegistry.h"

namespace Spec::Types::Runners {

    class DefaultRunner : public ISpecRunner {
    public:
        bool RunSetup(
            std::shared_ptr<SpecTest> setup, std::shared_ptr<SpecTestResult> testResult,
            std::vector<std::shared_ptr<ISpecExceptionHandler>> exceptionHandlers
        ) {
            if (setup->IsTodo()) return true;
            return SpecExtensionsRegistry::RunAndHandleError(setup, *testResult, exceptionHandlers);
        }

        bool RunSetups(
            std::vector<std::shared_ptr<SpecTest>> setups, std::shared_ptr<SpecTestResult> testResult,
            std::vector<std::shared_ptr<ISpecExceptionHandler>> exceptionHandlers
        ) {
            for (auto& setup : setups) {
                if (!RunSetup(setup, testResult, exceptionHandlers)) return false;
            }
            return true;
        }

        bool RunTeardown(
            std::shared_ptr<SpecTest> teardown, std::shared_ptr<SpecTestResult> testResult,
            std::vector<std::shared_ptr<ISpecExceptionHandler>> exceptionHandlers
        ) {
            if (teardown->IsTodo()) return true;
            return SpecExtensionsRegistry::RunAndHandleError(teardown, *testResult, exceptionHandlers);
        }

        bool RunTeardowns(
            std::vector<std::shared_ptr<SpecTest>> teardown, std::shared_ptr<SpecTestResult> testResult,
            std::vector<std::shared_ptr<ISpecExceptionHandler>> exceptionHandlers
        ) {
            for (auto& teardown : teardown) {
                if (!RunTeardown(teardown, testResult, exceptionHandlers)) return false;
            }
            return true;
        }

        void RunTest(
            std::shared_ptr<SpecTest> test, std::shared_ptr<SpecTestResult> testResult,
            std::vector<std::shared_ptr<ISpecReporter>>         reporters,
            std::vector<std::shared_ptr<ISpecExceptionHandler>> exceptionHandlers
        ) {
            for (auto& reporter : reporters) reporter->BeginTest(test, *testResult);
            if (!test->IsTodo()) {
                if (RunSetups(test->GetGroup()->GetSetups(), testResult, exceptionHandlers)) {
                    SpecExtensionsRegistry::RunAndHandleError(test, *testResult, exceptionHandlers);
                    RunTeardowns(test->GetGroup()->GetTeardowns(), testResult, exceptionHandlers);
                }
            }
            for (auto& reporter : reporters) reporter->EndTest(test, *testResult);
        }

        void RunGroup(
            std::shared_ptr<SpecGroup> group, SpecGroupResult& resultGroup,
            std::vector<std::shared_ptr<ISpecReporter>>         reporters,
            std::vector<std::shared_ptr<ISpecExceptionHandler>> exceptionHandlers
        ) {
            for (auto& test : group->GetTests()) {
                auto testResult = resultGroup.NewTest(test->GetDescription());
                RunTest(test, testResult, reporters, exceptionHandlers);
            }
            for (auto& innerGroup : group->GetGroups()) RunGroup(innerGroup, resultGroup, reporters, exceptionHandlers);
        }

        void RunSpecs(
            std::shared_ptr<std::promise<bool>> complete, std::shared_ptr<SpecGroup> specs, SpecResults& results,
            std::vector<std::shared_ptr<ISpecReporter>>         reporters,
            std::vector<std::shared_ptr<ISpecExceptionHandler>> exceptionHandlers
        ) override {
            RunGroup(specs, *results.GetRoot(), reporters, exceptionHandlers);
            complete->set_value(true);
        }
    };
}
