#pragma once

#include <format>
#include <memory>
#include <optional>

#include "Spec/Types/SpecGroupResult.h"
#include "Spec/Types/SpecTestResultFailure.h"
#include "Spec/Types/SpecTestResultStatus.h"

namespace Spec::Types {

    class SpecTestResult {
        std::string                      _description;
        SpecTestResultStatus             _status = SpecTestResultStatus::NotRun;
        SpecTestResultFailure            _failure;
        std::shared_ptr<SpecGroupResult> _group;

    public:
        SpecTestResult(std::string description, std::shared_ptr<SpecGroupResult> group)
            : _description(description), _group(group) {}

        std::string GetDescription() { return _description; }
        void        SetDescription(std::string description) { _description = description; }

        std::shared_ptr<SpecGroupResult> GetGroup() { return _group; }
        void                             SetGroup(std::shared_ptr<SpecGroupResult> group) { _group = group; }

        SpecTestResultStatus GetStatus() { return _status; }

        void SetStatus(SpecTestResultStatus status) {
            if (_status == SpecTestResultStatus::NotRun) {
                _status = status;
                if (_group) {
                    _group->IncrementTotalTests();
                    if (status == SpecTestResultStatus::Passed) {
                        _group->IncrementTotalPassed();
                    } else if (status == SpecTestResultStatus::Failed) {
                        _group->IncrementTotalFailed();
                    }
                }
            }
        }

        void Pass() { SetStatus(SpecTestResultStatus::Passed); }
        void Fail() { SetStatus(SpecTestResultStatus::Failed); }

        bool Passed() { return _status == SpecTestResultStatus::Passed; }
        bool Failed() { return _status == SpecTestResultStatus::Failed; }

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
