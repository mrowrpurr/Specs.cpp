#pragma once

#include "Spec/Types/ISpecRunner.h"

namespace Spec::Types::Runners {

    class SimpleRunner : public ISpecRunner {
    public:
        void RunTest(
            SpecTest& test, SpecResultGroup& resultGroup, std::vector<std::shared_ptr<ISpecReporter>> reporters
        ) {
            Print("Test: {}", test.GetDescription());
            try {
                // This should be like .Start() and then have a .Wait() or .Get() or something
                test.Run();
                Print("PASS");
                // resultGroup.AddResult(SpecResult::Pass(test.GetDescription()));
            } catch (const std::exception& e) {
                // resultGroup.AddResult(SpecResult::Fail(test.GetDescription(), e.what()));
                Print("FAIL: exception {}", e.what());
            } catch (const std::string& e) {
                // resultGroup.AddResult(SpecResult::Fail(test.GetDescription(), e));
                Print("FAIL: string {}", e);
            } catch (const char* e) {
                // resultGroup.AddResult(SpecResult::Fail(test.GetDescription(), e));
                Print("FAIL: char {}", e);
            } catch (...) {
                // resultGroup.AddResult(SpecResult::Fail(test.GetDescription(), "Unknown exception"));
                Print("FAIL");
            }
        }

        void RunGroup(
            SpecGroup& group, SpecResultGroup& resultGroup, std::vector<std::shared_ptr<ISpecReporter>> reporters
        ) {
            Print("Group: {}", group.GetDescription());
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
