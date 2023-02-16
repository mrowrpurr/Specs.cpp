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

    public:
        void BeginTest(SpecTest&) override {}
        void EndTest(SpecTest& test, bool passed, const std::string& failureMessage) override {
            std::string testDescription = test.GetDescription();
            auto        group           = test.GetGroup();
            while (group) {
                testDescription = group->GetDescription() + " " + testDescription;
                group           = group->GetParent();
            }
            if (passed)
                PrintPassed(testDescription);
            else
                PrintFailed(testDescription, failureMessage);
        }
        void BeginGroup(SpecGroup& group) override {}
        void EndGroup(SpecGroup&) override {}
    };
}
