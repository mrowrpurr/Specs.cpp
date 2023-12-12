#pragma once

#include <Specs/API.h>
#include <Specs/SpecCodeBlock.h>
#include <Specs/SpecComponent.h>
#include <Specs/SpecDone.h>
#include <Specs/SpecGroup.h>
#include <Specs/SpecSetup.h>
#include <Specs/SpecTeardown.h>
#include <Specs/SpecTest.h>
#include <_Log_.h>

#include <memory>
#include <string_view>
#include <vector>

namespace SpecsCpp {

    class GlobalSpecGroup {
        std::vector<ISpecGroup*> _currentGroupStack;

        ISpecGroup* _currentTopLevelGroup = nullptr;

        // A place to store some memory! These go here and never leave :)
        std::vector<std::unique_ptr<SpecTest>>     _registeredSpecs;
        std::vector<std::unique_ptr<SpecSetup>>    _registeredSetups;
        std::vector<std::unique_ptr<SpecTeardown>> _registeredTeardowns;
        std::vector<std::unique_ptr<SpecGroup>>    _registeredGroups;

    public:
        GlobalSpecGroup() {
            // GlobalSpecGroup comes with a root group
            auto rootGroup = std::make_unique<SpecGroup>(nullptr, "");
            _registeredGroups.push_back(std::move(rootGroup));
            _currentGroupStack.push_back(_registeredGroups.back().get());
        }

        // Or seed it with your own root group
        GlobalSpecGroup(ISpecGroup* rootGroup) { _currentGroupStack.push_back(rootGroup); }

        static GlobalSpecGroup& instance() {
            static GlobalSpecGroup instance;
            return instance;
        }

        ISpecGroup* root() const { return _registeredGroups.front().get(); }
        ISpecGroup* get() const {
            return _currentGroupStack.empty() ? nullptr : _currentGroupStack.back();
        }
        void push(ISpecGroup* group) { _currentGroupStack.push_back(group); }
        void pop() { _currentGroupStack.pop_back(); }

        void register_spec(std::string_view description, std::unique_ptr<SpecCodeBlock> codeBlock) {
            if (auto* group = get()) {
                auto  spec = std::make_unique<SpecTest>(get(), description, std::move(codeBlock));
                auto* specPtr = spec.get();
                _registeredSpecs.push_back(std::move(spec));
                group->add_spec(specPtr);
            } else {
                _Log_("register_spec() called but no group is active!");
            }
        }

        // TODO
        void register_group(
            std::string_view description, std::unique_ptr<SpecCodeBlock> codeBlock
        ) {
            if (auto* group = get()) {
                auto  specGroup    = std::make_unique<SpecGroup>(get(), description);
                auto* specGroupPtr = specGroup.get();
                _registeredGroups.push_back(std::move(specGroup));
                group->add_group(_registeredGroups.back().get());

                // Evaluate the group block (with this group being the 'current group')
                push(specGroupPtr);
                codeBlock->run(group, nullptr, nullptr);
                pop();
            } else {
                _Log_("register_group() called but no group is active!");
            }
        }

        void register_setup(std::unique_ptr<SpecCodeBlock> codeBlock) {
            if (auto* group = get()) {
                auto Setup = std::make_unique<SpecSetup>(get(), std::move(codeBlock));
                _registeredSetups.push_back(std::move(Setup));
                group->add_setup(_registeredSetups.back().get());
            }
        }

        void register_teardown(std::unique_ptr<SpecCodeBlock> codeBlock) {
            if (auto* group = get()) {
                auto Teardown = std::make_unique<SpecTeardown>(get(), std::move(codeBlock));
                _registeredTeardowns.push_back(std::move(Teardown));
                group->add_teardown(_registeredTeardowns.back().get());
            }
        }

        void register_group_fn(std::string_view description, FunctionPointer<void()> body) {
            register_group(description, std::make_unique<SpecCodeBlock>(std::move(body)));
        }

        void register_spec_fn(std::string_view description, FunctionPointer<void()> body) {
            register_spec(description, std::make_unique<SpecCodeBlock>(std::move(body)));
        }

        void register_spec_fn(std::string_view description, FunctionPointer<void(SpecDone)> body) {
            register_spec(description, std::make_unique<SpecCodeBlock>(std::move(body)));
        }

        void register_setup_fn(FunctionPointer<void()> body) {
            register_setup(std::make_unique<SpecCodeBlock>(std::move(body)));
        }

        void register_setup_fn(FunctionPointer<void(SpecDone)> body) {
            register_setup(std::make_unique<SpecCodeBlock>(std::move(body)));
        }

        void register_teardown_fn(FunctionPointer<void()> body) {
            register_teardown(std::make_unique<SpecCodeBlock>(std::move(body)));
        }

        void register_teardown_fn(FunctionPointer<void(SpecDone)> body) {
            register_teardown(std::make_unique<SpecCodeBlock>(std::move(body)));
        }

        void clear_top_level_group() {
            if (auto* group = get()) {
                // Is there another top-level group? Let's pop it off
                if (_currentTopLevelGroup) {
                    while (get() != _currentTopLevelGroup) pop();
                    if (get() == _currentTopLevelGroup) pop();
                }
                _currentTopLevelGroup = nullptr;
            }
        }

        void register_top_level_group(std::string_view description) {
            if (auto* group = get()) {
                // Is there another top-level group? Let's pop it off
                clear_top_level_group();

                auto  specGroup       = std::make_unique<SpecGroup>(get(), description);
                auto* specGroupPtr    = specGroup.get();
                _currentTopLevelGroup = specGroupPtr;
                _registeredGroups.push_back(std::move(specGroup));
                group->add_group(specGroupPtr);
                push(specGroupPtr);
            }
        }
    };
}
