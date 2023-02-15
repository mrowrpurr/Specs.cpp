#pragma once

#include "Spec/Types/ISpecRunner.h"

namespace Spec::Types::Runners {

    /**
     * Or let's do it another way.
     *
     * The goal is: Something that will POPULATE the SpecResults.
     *              And the runner can do whatever else it wants to.
     *              Basically this should do EVERYTHING except queue the spec?
     *              MAYBE: try making a PARALLEL runner *first* and extrapolate from there?
     */

    class BaseSpecRunner : public ISpecRunner {
    public:
        virtual void RunTest()  = 0;
        virtual void RunGroup() = 0;

        void BaseRunTest(SpecTest& test, SpecResults& results, std::vector<std::shared_ptr<ISpecReporter>> reporters) {
            // session.BeginTest(test);
            // try {
            //     // test.body(test);
            //     session.EndTest(test, true, "");
            // } catch (const std::exception& ex) {
            //     session.EndTest(test, false, ex.what());
            // } catch (const char* ex) {
            //     session.EndTest(test, false, ex);
            // } catch (...) {
            //     session.EndTest(test, false, "Unknown exception");
            // }
        }

        void BaseRunGroup(
            SpecGroup& group, SpecResults& results, std::vector<std::shared_ptr<ISpecReporter>> reporters
        ) {
            // session.BeginGroup(group);
            // for (auto& test : group.tests) RunTest(test, session);
            // for (auto& innerGroup : group.groups) RunGroup(innerGroup, session);
            // session.EndGroup(group);
        }

        void RunSpecs(
            std::shared_ptr<std::promise<bool>> complete, SpecRegistry& registry, SpecResults& results,
            std::vector<std::shared_ptr<ISpecReporter>> reporters
        ) override {
            Print("RUN IT!");
            RunGroup complete->set_value(true);
        }
    };
}
