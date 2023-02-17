#pragma once

#include <format>
#include <memory>

#include "Spec/Types/SpecGroupResult.h"
#include "Spec/Types/SpecTestResultFailure.h"

namespace Spec::Types {

    class SpecTestResult {
        std::string                      _description;
        bool                             _passed;  // TODO <-- make this an optional!
        SpecTestResultFailure            _failure;
        std::shared_ptr<SpecGroupResult> _group;

    public:
        SpecTestResult(std::string description, std::shared_ptr<SpecGroupResult> group)
            : _description(description), _group(group) {}

        std::string GetDescription() { return _description; }
        void        SetDescription(std::string description) { _description = description; }

        std::shared_ptr<SpecGroupResult> GetGroup() { return _group; }
        void                             SetGroup(std::shared_ptr<SpecGroupResult> group) { _group = group; }

        void SetPassed(bool passed) {
            _passed = passed;
            if (_group) {
                _group->IncrementTotalTests();
                if (passed) {
                    _group->IncrementTotalPassed();
                } else {
                    _group->IncrementTotalFailed();
                }
            }
        }
        void Pass() { SetPassed(true); }
        void Fail() { SetPassed(false); }
        bool Passed() { return _passed; }
        bool Failed() { return !_passed; }

        SpecTestResultFailure GetFailure() { return _failure; }

        void SetFailure(SpecTestResultFailure failure) {
            _failure = failure;
            Fail();
        }
        void SetFailure(std::string message) {
            _failure = SpecTestResultFailure{message};
            Fail();
        }
        void SetFailure(std::string message, std::string fileName, unsigned int lineNumber) {
            _failure = SpecTestResultFailure(message, fileName, lineNumber);
            Fail();
        }

        std::string GetFailureMessage() { return _failure.GetMessage(); }
        std::string GetFailureMessageWithFileLocation() {
            if (_failure.HasFileLocation()) {
                return std::format(
                    "{} ({}:{})", _failure.GetMessage(), _failure.GetFileName(), _failure.GetLineNumber()
                );
            } else {
                return _failure.GetMessage();
            }
        }
    };
}
