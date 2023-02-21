#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Specs/SpecGlobalScope.h"

namespace Specs {

    class SpecTestCase;

    //! Represents a group of SpecTestCase test cases and other children SpecTestGroup.
    class SpecTestGroup {
        std::string                                 _description = "";
        std::shared_ptr<SpecTestGroup>              _parent;
        std::vector<std::shared_ptr<SpecTestCase>>  _tests;
        std::vector<std::shared_ptr<SpecTestGroup>> _groups;
        std::vector<std::shared_ptr<SpecTestCase>>  _setups;
        std::vector<std::shared_ptr<SpecTestCase>>  _teardowns;
        std::vector<std::shared_ptr<SpecTestCase>>  _groupSetups;
        std::vector<std::shared_ptr<SpecTestCase>>  _groupTeardowns;

    public:
        //! Creates a new SpecTestGroup
        SpecTestGroup() = default;

        //! Creates a new SpecTestGroup with the given description and parent.
        SpecTestGroup(const std::string& description, std::shared_ptr<SpecTestGroup> parent)
            : _description(description), _parent(parent) {}

        //! Gets the description of this test group.
        std::string GetDescription() { return _description; }

        //! Sets the description of this test group.
        void SetDescription(std::string description) { _description = description; }

        //! Gets the full description of this test group including the parent's description.
        std::string GetFullDescription() {
            if (_parent && !_parent->IsRoot())
                return _parent->GetFullDescription() + SpecGlobalScope::Get().GetTestDescriptionSeparator() +
                       _description;
            else
                return _description;
        }

        //! Gets the parent of this test group.
        std::weak_ptr<SpecTestGroup> GetParent() { return _parent; }

        //! Gets whether this test group is the root test group.
        bool IsRoot() { return !_parent; }

        //! Sets the parent of this test group.
        void SetParent(std::shared_ptr<SpecTestGroup> parent) { _parent = parent; }

        //! Gets the test cases in this test group.
        std::vector<std::shared_ptr<SpecTestCase>>& GetTestCases() { return _tests; }

        //! Gets the test groups in this test group.
        std::vector<std::shared_ptr<SpecTestGroup>>& GetTestGroups() { return _groups; }

        //! Gets the setup test cases in this test group.
        std::vector<std::shared_ptr<SpecTestCase>>& GetSetups() { return _setups; }

        //! Gets the teardown test cases in this test group.
        std::vector<std::shared_ptr<SpecTestCase>>& GetTeardowns() { return _teardowns; }

        //! Gets the group setup test cases in this test group.
        std::vector<std::shared_ptr<SpecTestCase>>& GetGroupSetups() { return _groupSetups; }

        //! Gets the group teardown test cases in this test group.
        std::vector<std::shared_ptr<SpecTestCase>>& GetGroupTeardowns() { return _groupTeardowns; }

        //! Adds a test case to this test group.
        void AddTestCase(std::shared_ptr<SpecTestCase> test) { _tests.push_back(test); }

        //! Adds a test group to this test group.
        void AddTestGroup(std::shared_ptr<SpecTestGroup> group) { _groups.push_back(group); }

        //! Adds a setup test case to this test group.
        void AddSetup(std::shared_ptr<SpecTestCase> setup) { _setups.push_back(setup); }

        //! Adds a teardown test case to this test group.
        void AddTeardown(std::shared_ptr<SpecTestCase> teardown) { _teardowns.push_back(teardown); }

        //! Adds a group setup test case to this test group.
        void AddGroupSetup(std::shared_ptr<SpecTestCase> groupSetup) { _groupSetups.push_back(groupSetup); }

        //! Adds a group teardown test case to this test group.
        void AddGroupTeardown(std::shared_ptr<SpecTestCase> groupTeardown) { _groupTeardowns.push_back(groupTeardown); }
    };
}
