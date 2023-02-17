#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Spec/SpecTest.h"

namespace Spec {

    //! Represents a collection of child SpecTest and other SpecGroup.
    class SpecGroup {
        std::string                             _description;
        std::weak_ptr<SpecGroup>                _parent;
        std::vector<SpecTest>                   _setups;
        std::vector<SpecTest>                   _teardowns;
        std::vector<std::shared_ptr<SpecTest>>  _tests;
        std::vector<std::shared_ptr<SpecGroup>> _groups;

    public:
        SpecGroup() : SpecGroup("", nullptr) {}
        SpecGroup(const std::string& description, std::shared_ptr<SpecGroup> parent)
            : _description(description), _parent(parent) {}

        std::weak_ptr<SpecGroup>& GetParent() { return _parent; }
        std::string               GetDescription() { return _description; }
        std::string               GetFullDescription() {
            if (IsRoot()) return _description;
            if (_parent.lock()->GetFullDescription().empty()) return _description;
            return _parent.lock()->GetFullDescription() + " :: " + _description;
        }

        void AddTest(std::shared_ptr<SpecTest> test) { _tests.push_back(test); }
        void AddGroup(std::shared_ptr<SpecGroup> group) { _groups.push_back(group); }

        void AddSetup(const SpecTest& setup) { _setups.push_back(setup); }
        void AddTeardown(const SpecTest& teardown) { _teardowns.push_back(teardown); }
        void AddTest(const SpecTest& test) { _tests.push_back(std::make_shared<SpecTest>(test)); }
        void AddGroup(const SpecGroup& group) { _groups.push_back(std::make_shared<SpecGroup>(group)); }

        std::vector<SpecTest>&                   GetSetups() { return _setups; }
        std::vector<SpecTest>&                   GetTeardowns() { return _teardowns; }
        std::vector<std::shared_ptr<SpecTest>>&  GetTests() { return _tests; }
        std::vector<std::shared_ptr<SpecGroup>>& GetGroups() { return _groups; }

        bool IsRoot() const { return _parent.lock() == nullptr; }
    };

    // Hacky header-only grossness which we should possibily reorganize code to avoid
    std::string SpecTest::GetFullDescription() {
        if (_parent->IsRoot()) return _description;
        return _parent->GetFullDescription() + " :: " + _description;
    }
}
