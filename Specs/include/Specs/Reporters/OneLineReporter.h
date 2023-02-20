#pragma once

#include <Windows.h>

#include <iostream>

#include "Specs/ISpecReporter.h"

namespace Specs::Reporters {

    //! `Specs.cpp` reporter which prints out a single line per test case.
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
        void BeginTestCase(std::shared_ptr<SpecTestCase> testCase) override {}

        void EndTestCase(std::shared_ptr<SpecTestCase> testCase, SpecTestCaseResult testResult) override {
            if (testResult.Passed()) {
                PrintPassed(testCase->GetFullDescription());
            } else if (testResult.Failed()) {
                PrintFailed(testCase->GetFullDescription(), testResult.GetFailureMessage());
            } else {
                PrintNotRun(testCase->GetFullDescription());
            }
        }

        void BeginTestGroup(std::shared_ptr<SpecTestGroup> testGroup) override {}
        void EndTestGroup(std::shared_ptr<SpecTestGroup> testGroup) override {}
    };
}