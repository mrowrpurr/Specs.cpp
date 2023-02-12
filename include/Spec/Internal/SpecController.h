#pragma once

#include <atomic>
#include <functional>
#include <iostream>
#include <optional>
#include <string>

#include "Spec/SpecGroup.h"
#include "Spec/SpecTest.h"

namespace Spec::Internal {

    void Print(const std::string& text) { std::cout << text << std::endl; }

    class SpecController {
        ~SpecController()                                = default;
        SpecController(const SpecController&)            = delete;
        SpecController(SpecController&&)                 = delete;
        SpecController& operator=(const SpecController&) = delete;
        SpecController& operator=(SpecController&&)      = delete;

        std::shared_ptr<SpecGroup> _rootSpecGroup;

        SpecController() {
            _rootSpecGroup              = std::make_shared<SpecGroup>();
            _rootSpecGroup->description = "!ROOT!";
        }

        std::shared_ptr<SpecGroup> _currentlyEvaluatingGroup{nullptr};

    public:
        static SpecController& GetSingleton() {
            static SpecController singleton;
            return singleton;
        }

        void DefineSpecGroup(const std::string& description, std::function<void()> body) {
            auto parent =
                _currentlyEvaluatingGroup == nullptr ? _rootSpecGroup : _currentlyEvaluatingGroup;

            Print(std::format("DEFINE: group '{}' parent '{}'", description, parent->description));

            auto group         = std::make_shared<SpecGroup>();
            group->description = description;

            _currentlyEvaluatingGroup = group;

            body();

            parent->groups.emplace_back(*group);
        }

        void DefineSpecTest(const std::string& description, std::function<void(SpecTest&)> body) {
            SpecTest _test{.description = description, .body = body};
            auto     parent = _currentlyEvaluatingGroup;
            Print(std::format("DEFINE: test '{}' PARENT '{}'", description, parent->description));
            parent->tests.emplace_back(std::move(_test));
        }

        // TODO setup , teardown
        void RunSpecGroup(SpecGroup group) {
            currentIndent.append("  ");
            Print(std::format("{}RUN GROUP: {}", currentIndent, group.description));
            for (auto& test : group.tests) {
                Print(std::format("{}>> RUN TEST: {}", currentIndent, test.description));
                test.body(test);
            }
            for (auto& innerGroup : group.groups) RunSpecGroup(innerGroup);
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
