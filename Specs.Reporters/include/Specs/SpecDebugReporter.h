#pragma once

#include <Specs/API.h>
#include <_Log_.h>
#include <string_format.h>

#include "Utilities/PrintColor.h"

namespace SpecsCpp {

    class SpecDebugReporter : public ISpecReporter {
        void report_start() override { _Log_(">>>> START SUITE"); }

        void report_spec_begin(ISpec* spec) override {}

        void report_setup(ISpecRunResult* result) override {}

        void report_spec(ISpecRunResult* result) override {}

        void report_teardown(ISpecRunResult* result) override {}

        void report_spec_result(ISpecRunResult* result) override {
            switch (result->status()) {
                case SpecsCpp::RunResultStatus::Passed:
                    Colors::PrintColor(
                        string_format("\n[PASSED] {}\n", result->spec()->full_description()),
                        Colors::Color::Green
                    );
                    break;
                case SpecsCpp::RunResultStatus::Failed:
                    Colors::PrintColor(
                        string_format("\n[FAILED] {}\n", result->spec()->full_description()),
                        Colors::Color::Red
                    );
                    if (auto* message = result->message())
                        Colors::PrintColor(
                            string_format("\n{}\n", message), Colors::Color::DarkGray
                        );
                    break;
                case SpecsCpp::RunResultStatus::NotRun:
                    Colors::PrintColor(
                        string_format("\n[NOT RUN] {}\n", result->spec()->full_description()),
                        Colors::Color::Yellow
                    );
                    break;
                case SpecsCpp::RunResultStatus::Timeout:
                    Colors::PrintColor(
                        string_format("\n[TIMEOUT] {}\n", result->spec()->full_description()),
                        Colors::Color::LightRed
                    );
                    break;
            }
        }

        void report_suite(ISpecSuiteRunResult* result) override {
            Colors::Color foregroundColor = Colors::Color::White;
            Colors::Color backgroundColor = Colors::Color::Yellow;

            if (result->passed() > 0) backgroundColor = Colors::Color::Green;
            if (result->failed() > 0) backgroundColor = Colors::Color::Red;

            std::string output;

            if (result->failed() > 0) output += string_format("{} failed", result->failed());

            if (result->passed() > 0) {
                if (!output.empty()) output += ", ";
                output += string_format("{} passed", result->passed());
            }

            if (result->not_run() > 0) {
                if (!output.empty()) output += ", ";
                output += string_format("{} not run", result->not_run());
            }

            Colors::PrintColor(string_format("\n{}", output), foregroundColor, backgroundColor);
        }
    };
}
