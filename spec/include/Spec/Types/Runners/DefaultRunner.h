#pragma once

#include <format>
#include <memory>
#include <stacktrace>

#include "Spec/Types/ISpecRunner.h"
#include "Spec/Types/SpecExtensionsRegistry.h"

namespace Spec::Types::Runners {

    class DefaultRunner : public ISpecRunner {
    public:
        void RunTest(
            std::shared_ptr<SpecTest> test, SpecGroupResult& resultGroup,
            std::vector<std::shared_ptr<ISpecReporter>>         reporters,
            std::vector<std::shared_ptr<ISpecExceptionHandler>> exceptionHandlers
        ) {
            auto testResult = resultGroup.NewTest(test->GetDescription());
            for (auto& reporter : reporters) reporter->BeginTest(test, *testResult);
            if (!test->IsTodo()) SpecExtensionsRegistry::RunAndHandleError(test, *testResult, exceptionHandlers);
            for (auto& reporter : reporters) reporter->EndTest(test, *testResult);
        }

        void RunGroup(
            std::shared_ptr<SpecGroup> group, SpecGroupResult& resultGroup,
            std::vector<std::shared_ptr<ISpecReporter>>         reporters,
            std::vector<std::shared_ptr<ISpecExceptionHandler>> exceptionHandlers
        ) {
            for (auto& test : group->GetTests()) RunTest(test, resultGroup, reporters, exceptionHandlers);
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
