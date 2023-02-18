#pragma once

#include <Windows.h>

#include <iostream>

#include "Spec/Types/ISpecReporter.h"

namespace Spec::Types::Reporters {

    class OneLineReporter : public ISpecReporter {
        void PrintPassed(const std::string& testDescription) {
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            std::cout << "PASS: " << testDescription << std::endl;
            SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        void PrintFailed(const std::string& testDescription, const std::string& failureMessage) {
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
            if (!failureMessage.empty()) {
                std::cout << "FAIL: " << testDescription << " (" << failureMessage << ")" << std::endl;
            } else {
                std::cout << "FAIL: " << testDescription << std::endl;
            }
            SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        void PrintNotRun(const std::string& testDescription) {
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            std::cout << "NOT RUN: " << testDescription << std::endl;
            SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }

    public:
        void BeginTest(std::shared_ptr<SpecTest>, SpecTestResult&) override {}
        void EndTest(std::shared_ptr<SpecTest> test, SpecTestResult& result) override {
            if (result.Passed()) {
                PrintPassed(test->GetFullDescription());
            } else if (result.Failed()) {
                PrintFailed(test->GetFullDescription(), result.GetFailureMessageWithFileLocation());
            } else {
                PrintNotRun(test->GetFullDescription());
            }
        }
        void BeginSetup(std::shared_ptr<SpecTest>, SpecTestResult&) override {}
        void EndSetup(std::shared_ptr<SpecTest>, SpecTestResult&) override {}
        void BeginTeardown(std::shared_ptr<SpecTest>, SpecTestResult&) override {}
        void EndTeardown(std::shared_ptr<SpecTest>, SpecTestResult&) override {}
        void BeginGroup(SpecGroup&, SpecGroupResult&) override {}
        void EndGroup(SpecGroup&, SpecGroupResult&) override {}
    };
}
