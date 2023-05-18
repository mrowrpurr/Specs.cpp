#pragma once

#include <string>

#include "../DSL/Components/Functions/Print.h"
#include "../ISpecReporter.h"

namespace Specs::Reporters {

    //! `Specs.cpp` reporter which prints out indented test groups and test cases on individual lines.
    class DocumentationReporter : public ISpecReporter {
        std::string _indent;

        void BeginTestCase(std::shared_ptr<SpecTestCase> testCase) override {
            Print("{}{}", _indent, testCase->GetFullDescription());
        }

        void EndTestCase(std::shared_ptr<SpecTestCase> testCase, SpecTestCaseResult testResult) override {
            if (!testResult.Passed()) {
                Print("{}  {}", _indent, testResult.GetFailureMessage());
            }
        }

        void BeginTestGroup(std::shared_ptr<SpecTestGroup> testGroup) override {
            Print("{}{}", _indent, testGroup->GetFullDescription());
            _indent += "  ";
        }

        void EndTestGroup(std::shared_ptr<SpecTestGroup> testGroup) override {
            _indent = _indent.substr(0, _indent.size() - 2);
        }
    };
}