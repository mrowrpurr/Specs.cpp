#pragma once

#include <snowhouse/snowhouse.h>

using namespace snowhouse;

#include <format>
#include <memory>
#include <stacktrace>

#include "Spec/Types/ISpecRunner.h"

namespace Spec::Types::Runners {

    class SimpleRunner : public ISpecRunner {
    public:
        void RunTest(
            SpecTest& test, SpecResultGroup& resultGroup, std::vector<std::shared_ptr<ISpecReporter>> reporters
        ) {
            for (auto& reporter : reporters) reporter->BeginTest(test);
            try {
                test.Run();
                for (auto& reporter : reporters) reporter->EndTest(test, true, "");
            } catch (const char* e) {
                for (auto& reporter : reporters) reporter->EndTest(test, false, e);
            } catch (std::string e) {
                for (auto& reporter : reporters) reporter->EndTest(test, false, e);
            } catch (std::exception& e) {
                for (auto& reporter : reporters) reporter->EndTest(test, false, e.what());
            } catch (...) {
                for (auto& reporter : reporters) reporter->EndTest(test, false, "Unknown exception!");
            }
        }

        void RunGroup(
            SpecGroup& group, SpecResultGroup& resultGroup, std::vector<std::shared_ptr<ISpecReporter>> reporters
        ) {
            for (auto& test : group.GetTests()) RunTest(test, resultGroup, reporters);
            for (auto& innerGroup : group.GetGroups()) RunGroup(innerGroup, resultGroup, reporters);
        }

        void RunSpecs(
            std::shared_ptr<std::promise<bool>> complete, SpecRegistry& registry, SpecResults& results,
            std::vector<std::shared_ptr<ISpecReporter>> reporters
        ) override {
            RunGroup(*registry.GetRoot(), *results.GetRoot(), reporters);
            complete->set_value(true);
        }
    };
}
