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
            // } catch (const std::exception& e) {
            //     for (auto& reporter : reporters) reporter->EndTest(test, false, e.what());
            // } catch (const std::string& e) {
            //     for (auto& reporter : reporters) reporter->EndTest(test, false, e);
            } catch (snowhouse::AssertionException& e) {
                // for (auto& reporter : reporters) reporter->EndTest(test, false, e.what());
                Print("SNOWHOUSE ERROR: {} FILE:{} LINE:{}", e.what(), e.line(), e.file());
            // } catch (snowhouse::Exception& e) {
                // for (auto& reporter : reporters) reporter->EndTest(test, false, e.what()
            } catch (const char* e) {
                Print("LET'S GET THE LINE NUMBER");
                auto entry = std::stacktrace::current();
                for (auto whatever : entry) {
                    Print("FILE: {} LINE: {}", whatever.source_file(), whatever.source_line());
                }
                // Print("FILE: {} LINE: {}", entry.source_file(), entry.source_line());
                

                // for (auto& reporter : reporters) {

                // }
                // reporter->EndTest(test, false, std::format("{} FILE:{} LINE:{}", e, __FILE__, __LINE__));
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
