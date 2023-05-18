#pragma once

#include <memory>

#include "SpecGlobalScope.h"
#include "SpecTestCase.h"
#include "SpecTestCaseParam.h"
#include "SpecTestGroup.h"

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

        // ! Creates a new SpecRegistry with the given test group.
        explicit SpecRegistry(std::shared_ptr<SpecTestGroup> tests) : _rootTestGroup(tests) {}

        //! Returns a SpecRegistry using the currently configured global test group (see SpecGlobalGroup).
        static SpecRegistry GlobalRegistry() { return SpecRegistry(SpecGlobalScope::Get().GetGlobalGroup()); }

        static void UsingGlobalTestGroup(std::shared_ptr<SpecTestGroup> testGroup, std::function<void()> body) {
            auto& globalScope       = SpecGlobalScope::Get();
            auto  previousTestGroup = globalScope.GetGlobalGroup();
            globalScope.SetGlobalGroup(testGroup);
            body();
            globalScope.SetGlobalGroup(previousTestGroup);
        }

        //! Registers a test case with the given description and body.
        std::shared_ptr<SpecTestCase> RegisterTestCase(
            const std::string& description, std::function<void(std::shared_ptr<SpecTestCaseParam>)> body
        ) {
            auto testCase = std::make_shared<SpecTestCase>(description, _rootTestGroup, body);
            _rootTestGroup->AddTestCase(testCase);
            return testCase;
        }

        //! Registers a test case with the given description in the provided test group.
        std::shared_ptr<SpecTestCase> RegisterTestCase(
            const std::string& description, std::shared_ptr<SpecTestGroup> testGroup,
            std::function<void(std::shared_ptr<SpecTestCaseParam>)> body
        ) {
            auto testCase = std::make_shared<SpecTestCase>(description, testGroup, body);
            testGroup->AddTestCase(testCase);
            return testCase;
        }

        //! Registers a test case with the given description.
        std::shared_ptr<SpecTestCase> RegisterTestCase(const std::string& description) {
            auto testCase = std::make_shared<SpecTestCase>(description, _rootTestGroup);
            _rootTestGroup->AddTestCase(testCase);
            return testCase;
        }

        //! Registers a test case with the given description in the provided test group.
        std::shared_ptr<SpecTestCase> RegisterTestCase(
            const std::string& description, std::shared_ptr<SpecTestGroup> testGroup
        ) {
            auto testCase = std::make_shared<SpecTestCase>(description, testGroup);
            testGroup->AddTestCase(testCase);
            return testCase;
        }

        //! Registers a test group with the given description and *immediately* executes the provided body.
        std::shared_ptr<SpecTestGroup> RegisterTestGroup(const std::string& description, std::function<void()> body) {
            auto testGroup = std::make_shared<SpecTestGroup>(description, _rootTestGroup);
            _rootTestGroup->AddTestGroup(testGroup);
            // XXX Will there *ever* be a time when we don't want to evaluate this block right away?
            UsingGlobalTestGroup(testGroup, body);
            return testGroup;
        }

        //! Registers a test group with the given description.
        std::shared_ptr<SpecTestGroup> RegisterTestGroup(const std::string& description) {
            auto testGroup = std::make_shared<SpecTestGroup>(description, _rootTestGroup);
            _rootTestGroup->AddTestGroup(testGroup);
            return testGroup;
        }

        //! Returns the root test group.
        std::shared_ptr<SpecTestGroup> GetRootTestGroup() const { return _rootTestGroup; }
    };
}