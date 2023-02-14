#pragma once

#include "Spec/SpecGroup.h"
#include "Spec/SpecRegistry.h"
#include "Spec/SpecTest.h"

namespace Spec {

    //! Handles discovery and registration of specs at runtime
    /**
     * Provides a overloads for discovering specs/groups in various formats
     */
    class SpecDiscovery {
        SpecRegistry& _registry;

        std::vector<std::shared_ptr<SpecGroup>> _groupStack;

        void EnsureRoot() {
            if (_groupStack.empty()) _groupStack.emplace_back(_registry.GetRoot());
        }

        void PushGroup(std::shared_ptr<SpecGroup> specGroup) {
            EnsureRoot();
            _groupStack.emplace_back(specGroup);
        }

        void PopGroup() { _groupStack.pop_back(); }

        std::shared_ptr<SpecGroup> CurrentGroup() {
            EnsureRoot();
            return _groupStack.back();
        }

    public:
        SpecDiscovery(SpecRegistry& registry) : _registry(registry) {}

        void DiscoverGroup(const std::string& description, std::function<void(SpecGroup&)> body) {
            auto group         = std::make_shared<SpecGroup>();
            group->description = description;
            PushGroup(group);
            body(*group);
            PopGroup();
            CurrentGroup()->groups.emplace_back(*group);
        }

        void DiscoverGroup(const std::string& description, std::function<void()> body) {
            DiscoverGroup(description, [body](auto&) { body(); });
        }

        void DiscoverTest(const std::string& description, std::function<void(SpecTest&)> body) {
            CurrentGroup()->tests.emplace_back(SpecTest{.description = description, .body = body});
        }

        void DiscoverTest(const std::string& description, std::function<void()> body) {
            DiscoverTest(description, [body](auto&) { body(); });
        }
    };
}
