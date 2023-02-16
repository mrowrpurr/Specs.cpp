#pragma once

#include <format>
#include <memory>
#include <stacktrace>

#include "Spec/Types/ISpecRunner.h"
#include "Spec/Types/SpecExtensionsRegistry.h"

namespace Spec::Types::Runners {

    class SimpleRunner : public ISpecRunner {
    public:
        void RunTest(
            SpecTest& test, SpecResultGroup& resultGroup, std::vector<std::shared_ptr<ISpecReporter>> reporters,
            std::vector<std::shared_ptr<ISpecExceptionHandler>> exceptionHandlers
        ) {
            for (auto& reporter : reporters) reporter->BeginTest(test);
            SpecExtensionsRegistry::RunAndHandleError(
                [&]() {
                    Print("BEFORE RUN");
                    test.Run();
                    Print("AFTER RUN");
                },
                exceptionHandlers
            );
            for (auto& reporter : reporters) reporter->EndTest(test, 0, "");
        }

        void RunGroup(
            SpecGroup& group, SpecResultGroup& resultGroup, std::vector<std::shared_ptr<ISpecReporter>> reporters,
            std::vector<std::shared_ptr<ISpecExceptionHandler>> exceptionHandlers
        ) {
            for (auto& test : group.GetTests()) RunTest(test, resultGroup, reporters, exceptionHandlers);
            for (auto& innerGroup : group.GetGroups()) RunGroup(innerGroup, resultGroup, reporters, exceptionHandlers);
        }

        void RunSpecs(
            std::shared_ptr<std::promise<bool>> complete, SpecRegistry& registry, SpecResults& results,
            std::vector<std::shared_ptr<ISpecReporter>>         reporters,
            std::vector<std::shared_ptr<ISpecExceptionHandler>> exceptionHandlers
        ) override {
            RunGroup(*registry.GetRoot(), *results.GetRoot(), reporters, exceptionHandlers);
            complete->set_value(true);
        }
    };
}
