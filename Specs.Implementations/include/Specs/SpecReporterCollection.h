#pragma once

#include <Specs/API.h>
#include <collections.h>

#include <string>

namespace SpecsCpp {

    class SpecReporterCollection : public ISpecReporterCollection {
        collections_map<std::string, ISpecReporter*> _reporters;

    public:
        void add(const char* name, ISpecReporter* reporter) override {
            _reporters[name] = reporter;
        }

        bool has(const char* name) const override { return _reporters.contains(name); }

        ISpecReporter* get(const char* name) const override {
            auto found = _reporters.find(name);
            if (found != _reporters.end()) return found->second;
            return nullptr;
        }

        void foreach_reporter(ForEachReporterFn* fn) const override {
            for (const auto& [name, reporter] : _reporters) fn->invoke(reporter);
        }

        void report_start() override {
            for (const auto& [name, reporter] : _reporters) reporter->report_start();
        }

        void report_spec_begin(ISpec* spec) override {
            for (const auto& [name, reporter] : _reporters) reporter->report_spec_begin(spec);
        }

        void report_setup(ISpecRunResult* result) override {
            for (const auto& [name, reporter] : _reporters) reporter->report_setup(result);
        }

        void report_spec(ISpecRunResult* result) override {
            for (const auto& [name, reporter] : _reporters) reporter->report_spec(result);
        }

        void report_teardown(ISpecRunResult* result) override {
            for (const auto& [name, reporter] : _reporters) reporter->report_teardown(result);
        }

        void report_spec_result(ISpecRunResult* result) override {
            for (const auto& [name, reporter] : _reporters) reporter->report_spec_result(result);
        }

        void report_suite_result(ISpecSuiteRunResult* result) override {
            for (const auto& [name, reporter] : _reporters) reporter->report_suite_result(result);
        }
    };
}