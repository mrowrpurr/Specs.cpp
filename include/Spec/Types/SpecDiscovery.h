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

        std::shared_ptr<SpecRegistry> GetRegistry() { return _registry; }
        void                          SetRegistry(std::shared_ptr<SpecRegistry> registry) { _registry = registry; }
        void SetRegistry(SpecRegistry& registry) { _registry = std::make_shared<SpecRegistry>(registry); }

        void DiscoverGroup(const std::string& description, std::function<void(SpecGroup&)> body) {
            if (!EnsureRoot()) return;
            auto group = std::make_shared<SpecGroup>(description, CurrentGroup());
            PushGroup(group);
            body(*group);
            PopGroup();
            CurrentGroup()->AddGroup(*group);
        }

        void DiscoverGroup(const std::string& description, std::function<void()> body) {
            DiscoverGroup(description, [body](auto&) { body(); });
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
