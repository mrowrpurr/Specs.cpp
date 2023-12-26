#pragma once

#include <Specs/API.h>

namespace SpecsCpp::TestHelpers {

    class MockTestReporter : public ISpecReporter {
        void report_start() override {}
        void report_suite_begin(unsigned int specCount) override {}
        void report_spec_begin(ISpec* spec) override {}
        void report_setup(ISpecRunResult* result) override {}
        void report_spec(ISpecRunResult* result) override {}
        void report_teardown(ISpecRunResult* result) override {}
        void report_spec_result(ISpecRunResult* result) override {}
        void report_suite_result(ISpecSuiteRunResult* result) override {}
    };
}
