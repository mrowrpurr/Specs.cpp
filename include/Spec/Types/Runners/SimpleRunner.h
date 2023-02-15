#pragma once

#include "Spec/Types/ISpecRunner.h"

namespace Spec::Types::Runners {

    class SimpleRunner : public ISpecRunner {
    public:
        void RunSpecs(
            std::promise<void>& complete, SpecRegistry& registry, SpecResults& results,
            std::vector<ISpecReporter> reporters
        ) override {}

        //     void RunTest(SpecTest& test, SpecSession& session) {
        //         session.BeginTest(test);
        //         try {
        //             test.body(test);
        //             session.EndTest(test, true, "");
        //         } catch (const std::exception& ex) {
        //             session.EndTest(test, false, ex.what());
        //         } catch (const char* ex) {
        //             session.EndTest(test, false, ex);
        //         } catch (...) {
        //             session.EndTest(test, false, "Unknown exception");
        //         }
        //     }

        //     void RunGroup(SpecGroup& group, SpecSession& session) {
        //         session.BeginGroup(group);
        //         for (auto& test : group.tests) RunTest(test, session);
        //         for (auto& innerGroup : group.groups) RunGroup(innerGroup, session);
        //         session.EndGroup(group);
        //     }

        // public:
        //     void RunSpecs(std::promise<void>& promise, SpecSession& session) override {
        //         auto specGroupRoot = session.GetContext().GetRegistry().GetRoot();
        //         RunGroup(*specGroupRoot, session);
        //         promise.set_value();
        //     }
    };
}
