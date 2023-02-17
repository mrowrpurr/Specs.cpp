#pragma once

#include "Spec/Types/SpecRegistry.h"

namespace Spec::Types {
    class SpecDiscovery {
        static SpecDiscovery                    _globalInstance;
        std::shared_ptr<SpecRegistry>           _registry{nullptr};
        std::vector<std::shared_ptr<SpecGroup>> _groupStack;

        bool EnsureRoot() {
            if (!_registry) return false;
            if (_groupStack.empty()) _groupStack.emplace_back(_registry->GetRoot());
            return true;
        }

        void PushGroup(std::shared_ptr<SpecGroup> specGroup) {
            if (!EnsureRoot()) return;
            _groupStack.emplace_back(specGroup);
        }

        void PopGroup() {
            if (!EnsureRoot()) return;
            _groupStack.pop_back();
        }

        std::shared_ptr<SpecGroup> CurrentGroup() {
            if (!EnsureRoot()) return nullptr;
            return _groupStack.back();
        }

    public:
        SpecDiscovery() = default;
        SpecDiscovery(std::shared_ptr<SpecRegistry> registry) : _registry(registry) {}

        static SpecDiscovery& GetGlobalInstance() { return _globalInstance; }
        static void           SetGlobalInstance(SpecDiscovery& instance) { _globalInstance = instance; }
        static void           UsingRegistry(std::shared_ptr<SpecRegistry> registry, std::function<void()> code) {
            // TODO XXX This is pretty gross. Clean it up :)
            auto& globalInstance = GetGlobalInstance();
            auto  oldRegistry    = globalInstance.GetRegistry();
            auto  oldGroupStack  = globalInstance._groupStack;
            globalInstance.SetRegistry(registry);
            globalInstance._groupStack.clear();
            code();
            globalInstance.SetRegistry(oldRegistry);
            globalInstance._groupStack = oldGroupStack;
        }
        static void UsingRegistry(SpecRegistry& registry, std::function<void()> code) {
            UsingRegistry(std::make_shared<SpecRegistry>(registry), code);
        }

        std::shared_ptr<SpecRegistry> GetRegistry() { return _registry; }
        void                          SetRegistry(std::shared_ptr<SpecRegistry> registry) { _registry = registry; }
        void SetRegistry(SpecRegistry& registry) { _registry = std::make_shared<SpecRegistry>(registry); }

        /** Starts a top-level group without adding any body to it.
         * Calling DiscoverGroup without a body always sets the current group to the root group.
         */
        void DiscoverGroup(const std::string& description) {
            _groupStack.clear();
            if (!EnsureRoot()) return;
            auto group = std::make_shared<SpecGroup>(description, CurrentGroup());
            _registry->GetRoot()->AddGroup(group);
            PushGroup(group);
        }

        void DiscoverGroup(const std::string& description, std::function<void(SpecGroup&)> body) {
            if (!EnsureRoot()) return;
            auto group = std::make_shared<SpecGroup>(description, CurrentGroup());
            CurrentGroup()->AddGroup(group);
            PushGroup(group);
            body(*group);
            PopGroup();
        }

        void DiscoverGroup(const std::string& description, std::function<void()> body) {
            DiscoverGroup(description, [body](auto&) { body(); });
        }

        void DiscoverTest(const std::string& description) {
            if (!EnsureRoot()) return;
            CurrentGroup()->AddTest(SpecTest(description, CurrentGroup()));
        }

        void DiscoverTest(const std::string& description, std::function<void(SpecTest&)> body) {
            if (!EnsureRoot()) return;
            CurrentGroup()->AddTest(SpecTest(description, CurrentGroup(), body));
        }

        void DiscoverTest(const std::string& description, std::function<void()> body) {
            DiscoverTest(description, [body](auto&) { body(); });
        }
    };

    SpecDiscovery SpecDiscovery::_globalInstance;
}
