#pragma once

#include "Specs/ISpecReporter.h"

namespace Specs::Reporters {

    //! `Specs.cpp` reporter which prints out indented test groups and test cases on individual lines.
    class DocumentationReporter : public ISpecReporter {
        void BeginTestCase(std::shared_ptr<SpecTestCaseRun> testCaseRun) override {
            Print(testCaseRun->GetTestCase()->GetFullDescription());
        }

        void EndTestCase(std::shared_ptr<SpecTestCaseRun> testCaseRun) override {}

        void BeginTestGroup(std::shared_ptr<SpecTestGroup> testGroup) override {
            Print(testGroup->GetFullDescription());
        }

        void EndTestGroup(std::shared_ptr<SpecTestGroup> testGroup) override {}
    };
}