#pragma once

#include <memory>
#include <string>
#include <vector>

namespace Spec::Types {

    class SpecTestResult;

    class SpecGroupResult : public std::enable_shared_from_this<SpecGroupResult> {
        unsigned int                                  _totalTests  = 0;
        unsigned int                                  _totalPassed = 0;
        unsigned int                                  _totalFailed = 0;
        std::vector<std::shared_ptr<SpecGroupResult>> _groups;
        std::vector<std::shared_ptr<SpecTestResult>>  _tests;
        std::weak_ptr<SpecGroupResult>                _parent;
        std::string                                   _description;

    public:
        SpecGroupResult() = default;
        SpecGroupResult(std::string description, std::shared_ptr<SpecGroupResult> parent = nullptr)
            : _parent(parent), _description(description) {}

        std::shared_ptr<SpecGroupResult> GetParent() { return _parent.lock(); }

        unsigned int GetTotalTests() { return _totalTests; }
        void         IncrementTotalTests() {
            _totalTests++;
            if (auto parent = GetParent()) parent->IncrementTotalTests();
        }

        unsigned int GetTotalPassed() { return _totalPassed; }
        void         IncrementTotalPassed() {
            _totalPassed++;
            if (auto parent = GetParent()) parent->IncrementTotalPassed();
        }

        unsigned int GetTotalFailed() { return _totalFailed; }
        void         IncrementTotalFailed() {
            _totalFailed++;
            if (auto parent = GetParent()) parent->IncrementTotalFailed();
        }

        std::string GetDescription() { return _description; }
        void        SetDescription(std::string description) { _description = description; }

        std::vector<std::shared_ptr<SpecGroupResult>> GetGroups() { return _groups; }
        void AddGroup(std::shared_ptr<SpecGroupResult> group) { _groups.push_back(group); }

        std::vector<std::shared_ptr<SpecTestResult>> GetTests() { return _tests; }
        void                            AddTest(std::shared_ptr<SpecTestResult> test) { _tests.push_back(test); }
        std::shared_ptr<SpecTestResult> NewTest(std::string description) {
            auto test = std::make_shared<SpecTestResult>(description, shared_from_this());
            AddTest(test);
            return test;
        }
    };
}
