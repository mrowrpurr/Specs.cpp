#pragma once

#include <functional>
#include <memory>
#include <optional>
#include <string>

#include "Specs/SpecTestGroup.h"

namespace Specs {

    class SpecTestCaseParam;

    //! Represents a single test case.
    class SpecTestCase {
        std::string                                                            _description;
        std::optional<std::function<void(std::shared_ptr<SpecTestCaseParam>)>> _body;
        std::shared_ptr<SpecTestGroup>                                         _parent;

    public:
        //! Creates a new SpecTestCase with the given description, body, and parent.
        SpecTestCase(
            const std::string& description, std::shared_ptr<SpecTestGroup> parent,
            std::function<void(std::shared_ptr<SpecTestCaseParam>)> body
        )
            : _description(description), _body(body), _parent(parent) {}

        //! Creates a new SpecTestCase with the given description and parent.
        SpecTestCase(const std::string& description, std::shared_ptr<SpecTestGroup> parent)
            : _description(description), _parent(parent) {}

        //! Gets the description of this test case.
        std::string GetDescription() { return _description; }

        //! Gets the full description of this test case including the parent's description.
        std::string GetFullDescription() {
            if (_parent) {
                return _parent->GetFullDescription() + " :: " + _description;
            } else {
                return _description;
            }
        }

        //! Sets the description of this test case.
        void SetDescription(std::string description) { _description = description; }

        //! Gets the parent of this test case.
        std::shared_ptr<SpecTestGroup> GetParent() { return _parent; }

        //! Sets the parent of this test case.
        void SetParent(std::shared_ptr<SpecTestGroup> parent) { _parent = parent; }

        //! Gets the body of this test case.
        std::optional<std::function<void(std::shared_ptr<SpecTestCaseParam>)>> GetBody() { return _body; }

        //! Sets the body of this test case.
        void SetBody(std::function<void(std::shared_ptr<SpecTestCaseParam>)> body) { _body = body; }
    };
}
