#pragma once

#include <optional>
#include <string>

namespace Specs {

    //! Represents the result of a single test case.
    class SpecTestCaseResult {
        std::optional<bool> _passed;
        std::string         _failureMessage;

    public:
        //! Creates a new test case result.
        SpecTestCaseResult() = default;

        //! Creates a new test case result.
        SpecTestCaseResult(bool passed, const std::string& failureMessage)
            : _passed(passed), _failureMessage(failureMessage) {}

        //! Returns whether the test case passed.
        bool Passed() {
            if (_passed.has_value()) return _passed.value();
            return false;
        }

        //! Returns whether the test case failed.
        bool Failed() {
            if (_passed.has_value()) return !_passed.value();
            return false;
        }

        //! Returns whether the test case was not run.
        bool NotRun() { return !_passed.has_value(); }

        //! Marks the test case as passed.
        void Pass() { _passed = true; }

        //! Marks the test case as failed.
        void Fail() { _passed = false; }

        //! Returns the failure message.
        std::string GetFailureMessage() { return _failureMessage; }

        //! Sets the failure message.
        void SetFailureMessage(const std::string& message) {
            _failureMessage = message;
            _passed         = false;
        }
    };
}