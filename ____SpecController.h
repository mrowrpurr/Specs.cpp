#pragma once

#include <atomic>
#include <format>
#include <functional>
#include <iostream>
#include <optional>
#include <string>

#include "Spec/SpecGroup.h"
#include "Spec/SpecTest.h"
#include "Spec/TEMP_PRINT.h"

namespace Spec::Internal {

    class SpecController {
        ~SpecController()                                = default;
        SpecController(const SpecController&)            = delete;
        SpecController(SpecController&&)                 = delete;
        SpecController& operator=(const SpecController&) = delete;
        SpecController& operator=(SpecController&&)      = delete;

        // This stuff should be in a Discovery thingy --- or Registry, even better!
        std::shared_ptr<SpecGroup> _rootSpecGroup;
        std::shared_ptr<SpecGroup> _currentlyEvaluatingGroup;

        SpecController() {
            _rootSpecGroup              = std::make_shared<SpecGroup>();
            _rootSpecGroup->description = "!ROOT!";
            _currentlyEvaluatingGroup   = _rootSpecGroup;
        }

    public:
        static SpecController& GetSingleton() {
            static SpecController singleton;
            return singleton;
        }

        void DefineSpecGroup(const std::string& description, std::function<void(SpecGroup&)> body) {
            auto parent = _currentlyEvaluatingGroup;
            Print("DEFINE: group '{}' parent '{}'", description, parent->description);
            auto group                = std::make_shared<SpecGroup>();
            group->description        = description;
            _currentlyEvaluatingGroup = group;
            body(*group);
            // parent->groups.emplace_back(*group);
            _currentlyEvaluatingGroup = parent;
        }

        void DefineSpecTest(const std::string& description, std::function<void(SpecTest&)> body) {
            Print("DefineSpecTest {}", description);
            SpecTest _test{.description = description, .body = body};
            auto     parent = _currentlyEvaluatingGroup;
            parent->tests.emplace_back(std::move(_test));
        }

        // TODO move to a SpecRunner, yo. With SpecReporter support.
        // TODO setup , teardown
        void RunSpecGroup(SpecGroup group) {
            Print("{}RUN GROUP: {}", currentIndent, group.description);
            for (auto& test : group.tests) {
                Print(std::format("{}>> RUN TEST: {}", currentIndent, test.description));
                test.body(test);
            }
            for (auto& innerGroup : group.groups) {
                auto indent = currentIndent;
                currentIndent.append("  ");
                RunSpecGroup(innerGroup);
                currentIndent = indent;
            }
        }

        std::string currentIndent = "";

        void RunSpecs() {
            Print("=-======================================");
            Print("~~~ RUN SPECS");
            RunSpecGroup(*_rootSpecGroup);
            Print("~~~ DONE");
        }
    };
}
