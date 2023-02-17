#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Spec/SpecTest.h"

namespace Spec {

    //! Represents a collection of child SpecTest and other SpecGroup.
    class SpecGroup {
        std::string                _description;
        std::shared_ptr<SpecGroup> _parent{nullptr};
        std::vector<SpecTest>      _setups;
        std::vector<SpecTest>      _teardowns;
        std::vector<SpecTest>      _tests;
        std::vector<SpecGroup>     _groups;

    public:
        SpecGroup(const std::string& description, std::shared_ptr<SpecGroup> parent)
            : _description(description), _parent(parent) {}

        std::shared_ptr<SpecGroup>& GetParent() { return _parent; }
        std::string                 GetDescription() { return _description; }
        std::string                 GetFullDescription() {
            if (IsRoot()) return _description;
            return _parent->GetFullDescription() + " " + _description;
        }

        void AddSetup(const SpecTest& setup) { _setups.push_back(setup); }
        void AddTeardown(const SpecTest& teardown) { _teardowns.push_back(teardown); }
        void AddTest(const SpecTest& test) { _tests.push_back(test); }
        void AddGroup(const SpecGroup& group) { _groups.push_back(group); }

        std::vector<SpecTest>&  GetSetups() { return _setups; }
        std::vector<SpecTest>&  GetTeardowns() { return _teardowns; }
        std::vector<SpecTest>&  GetTests() { return _tests; }
        std::vector<SpecGroup>& GetGroups() { return _groups; }

        bool IsRoot() const { return _parent == nullptr; }
    };

    // Hacky header-only grossness which we should possibily reorganize code to avoid
    std::string SpecTest::GetFullDescription() {
        if (_parent->IsRoot()) return _description;
        return _parent->GetFullDescription() + " " + _description;
    }
}
