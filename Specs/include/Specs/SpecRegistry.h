#pragma once

#include <memory>

#include "Specs/SpecTestCase.h"
#include "Specs/SpecTestCaseParam.h"
#include "Specs/SpecTestGroup.h"
#include "Specs/SpecTestGroupParam.h"

namespace Specs {

    //! Provides helper functions for registering test cases and groups in SpecTestGroup.
    /**
     * Exists so that we can have one class which knows about *both* SpecTestGroup *and* SpecTestCase to register both.
     */
    class SpecRegistry {
        std::shared_ptr<SpecTestGroup> _rootTestGroup;

    public:
        //! Creates a new SpecRegistry.
        SpecRegistry() : _rootTestGroup(std::make_shared<SpecTestGroup>()) {}

        //! Creates a new SpecRegistry with the given test group.
        explicit SpecRegistry(std::shared_ptr<SpecTestGroup> tests) : _rootTestGroup(tests) {}

        //! Registers a test case with the given description and body.
        void RegisterTestCase(
            const std::string& description, std::function<void(std::shared_ptr<SpecTestCaseParam>)> body
        ) {
            auto testCase = std::make_shared<SpecTestCase>(description, _rootTestGroup, body);
            _rootTestGroup->AddTestCase(testCase);
        }

        //! Registers a test case with the given description.
        void RegisterTestCase(const std::string& description) {
            auto testCase = std::make_shared<SpecTestCase>(description, _rootTestGroup);
            _rootTestGroup->AddTestCase(testCase);
        }

        //! Registers a test group with the given description and body.
        void RegisterTestGroup(
            const std::string& description, std::function<void(std::shared_ptr<SpecTestGroupParam>)> body
        ) {
            auto testGroup = std::make_shared<SpecTestGroup>(description, _rootTestGroup);
            _rootTestGroup->AddTestGroup(testGroup);
            // Optionally evaluate the body() here? To get the child test cases and groups registered?
        }

        //! Registers a test group with the given description.
        void RegisterTestGroup(const std::string& description) {
            auto testGroup = std::make_shared<SpecTestGroup>(description, _rootTestGroup);
            _rootTestGroup->AddTestGroup(testGroup);
        }
    };
}