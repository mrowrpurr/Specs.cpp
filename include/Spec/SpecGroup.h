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

        const std::string&                GetDescription() const { return _description; }
        const std::shared_ptr<SpecGroup>& GetParent() const { return _parent; }

        void AddSetup(const SpecTest& setup) { _setups.push_back(setup); }
        void AddTeardown(const SpecTest& teardown) { _teardowns.push_back(teardown); }
        void AddTest(const SpecTest& test) { _tests.push_back(test); }
        void AddGroup(const SpecGroup& group) { _groups.push_back(group); }

        bool IsRoot() const { return _parent == nullptr; }
    };
}
