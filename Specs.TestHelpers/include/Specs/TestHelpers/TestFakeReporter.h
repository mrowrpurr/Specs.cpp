#pragma once

#include <Specs/API.h>
#include <_Log_.h>
#include <collections.h>

#include <string_view>
#include <vector>

namespace SpecsCpp::TestHelpers {

    class TestFakeReporter : public ISpecReporter {
        collections_map<std::string, std::unique_ptr<ISpecRunResult>> _testResults;

    public:
        ISpecRunResult* test_result(std::string_view testName) {
            auto found = _testResults.find(testName.data());
            if (found != _testResults.end()) return found->second.get();
            return nullptr;
        }

        /* Interface */

        void report_start() override {}
        void report_suite_begin(unsigned int specCount) override {}
        void report_test_begin(ISpec* spec) override {}
        void report_setup(ISpecRunResult* result) override {}
        void report_test(ISpecRunResult* result) override {}
        void report_teardown(ISpecRunResult* result) override {}
        void report_test_result(ISpecRunResult* result) override {
            _testResults[result->spec()->full_description()] =
                std::unique_ptr<ISpecRunResult>(result->copy());
        }
        void report_suite_result(ISpecSuiteRunResult* result) override {}
    };
}
