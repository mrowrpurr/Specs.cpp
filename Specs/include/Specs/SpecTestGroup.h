#pragma once

#include <memory>
#include <string>
#include <vector>

namespace Specs {

    class SpecTestCase;

    //! Represents a group of SpecTestCase test cases and other children SpecTestGroup.
    class SpecTestGroup {
        std::string                                 _description;
        std::weak_ptr<SpecTestGroup>                _parent;
        std::vector<std::shared_ptr<SpecTestCase>>  _tests;
        std::vector<std::shared_ptr<SpecTestGroup>> _groups;
        std::vector<std::shared_ptr<SpecTestCase>>  _setups;
        std::vector<std::shared_ptr<SpecTestCase>>  _teardowns;
        std::vector<std::shared_ptr<SpecTestCase>>  _groupSetups;
        std::vector<std::shared_ptr<SpecTestCase>>  _groupTeardowns;

    public:
        //! Creates a new SpecTestGroup with the given description and parent.
        SpecTestGroup(const std::string& description, std::weak_ptr<SpecTestGroup> parent)
            : _description(description), _parent(parent) {}

        //! Gets the description of this test group.
        std::string GetDescription() { return _description; }

        //! Sets the description of this test group.
        void SetDescription(std::string description) { _description = description; }

        //! Gets the parent of this test group.
        std::weak_ptr<SpecTestGroup> GetParent() { return _parent; }

        //! Sets the parent of this test group.
        void SetParent(std::weak_ptr<SpecTestGroup> parent) { _parent = parent; }

        //! Gets the test cases in this test group.
        std::vector<std::shared_ptr<SpecTestCase>>& GetTests() { return _tests; }

        //! Gets the test groups in this test group.
        std::vector<std::shared_ptr<SpecTestGroup>>& GetGroups() { return _groups; }

        //! Gets the setup test cases in this test group.
        std::vector<std::shared_ptr<SpecTestCase>>& GetSetups() { return _setups; }

        //! Gets the teardown test cases in this test group.
        std::vector<std::shared_ptr<SpecTestCase>>& GetTeardowns() { return _teardowns; }

        //! Gets the group setup test cases in this test group.
        std::vector<std::shared_ptr<SpecTestCase>>& GetGroupSetups() { return _groupSetups; }

        //! Gets the group teardown test cases in this test group.
        std::vector<std::shared_ptr<SpecTestCase>>& GetGroupTeardowns() { return _groupTeardowns; }
    };
}
