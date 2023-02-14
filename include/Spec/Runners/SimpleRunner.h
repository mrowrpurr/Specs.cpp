#pragma once

#include "Spec/SpecRunner.h"

namespace Spec::Runners {

    class SimpleRunner : public SpecRunner {
    public:
        void RunTest(SpecTest& test, SpecReporter& reporter) {
            reporter.BeginTest(test);
            try {
                test.body(test);
                reporter.EndTest(test, true, "");
            } catch (const std::exception& ex) {
                reporter.EndTest(test, false, ex.what());
            } catch (const char* ex) {
                reporter.EndTest(test, false, ex);
            } catch (...) {
                reporter.EndTest(test, false, "Unknown exception");
            }
        }

        void RunGroup(SpecGroup& group, SpecReporter& reporter) {
            reporter.BeginGroup(group);
            for (auto& test : group.tests) RunTest(test, reporter);
            for (auto& innerGroup : group.groups) RunGroup(innerGroup, reporter);
            reporter.EndGroup(group);
        }

        void RunSpecs(std::promise<void>& promise, SpecSession& session, SpecReporter& reporter) override {
            auto specGroupRoot = session.GetContext().GetRegistry().GetRoot();
            RunGroup(*specGroupRoot, reporter);
            promise.set_value();
        }
    };
}
