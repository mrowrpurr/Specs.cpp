#pragma once

#include <Specs/API.h>
#include <Specs/SpecCodeBlock.h>
#include <Specs/SpecComponent.h>
#include <Specs/SpecGroup.h>
#include <Specs/SpecSetup.h>
#include <Specs/SpecTeardown.h>
#include <Specs/SpecTest.h>
#include <_Log_.h>
#include <collections.h>

#include <memory>
#include <string>
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

        collections_map<std::string, std::unique_ptr<SpecGroup>> _testTemplateGroups;

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
        void set(ISpecGroup* group) { _currentGroupStack.back() = group; }
        void push(ISpecGroup* group) { _currentGroupStack.push_back(group); }
        void pop() { _currentGroupStack.pop_back(); }

        void register_template(
            std::string_view templateName, std::unique_ptr<SpecCodeBlock> codeBlock
        ) {
            auto  templateGroup    = std::make_unique<SpecGroup>(nullptr, templateName);
            auto* templateGroupPtr = templateGroup.get();

            auto* currentGroup = get();
            set(templateGroupPtr);
            codeBlock->run(templateGroupPtr, nullptr, nullptr);
            set(currentGroup);

            _testTemplateGroups[templateName.data()] = std::move(templateGroup);
        }

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
            clear_top_level_group();

            if (auto* group = get()) {
                auto  specGroup       = std::make_unique<SpecGroup>(get(), description);
                auto* specGroupPtr    = specGroup.get();
                _currentTopLevelGroup = specGroupPtr;
                _registeredGroups.push_back(std::move(specGroup));
                group->add_group(specGroupPtr);
                push(specGroupPtr);
            }
        }

        void register_top_level_template(std::string_view templateName) {
            clear_top_level_group();

            if (auto* group = get()) {
                auto  specGroup       = std::make_unique<SpecGroup>(get(), templateName);
                auto* specGroupPtr    = specGroup.get();
                _currentTopLevelGroup = specGroupPtr;
                _testTemplateGroups[templateName.data()] = std::move(specGroup);
                push(specGroupPtr);
            }
        }

        void use_template(std::string_view templateName) {
            if (auto* group = get()) {
                auto found = _testTemplateGroups.find(templateName.data());
                if (found == _testTemplateGroups.end()) {
                    _Error_("Test template not found: {}", templateName);
                    return;
                }

                auto* templateGroup = found->second.get();
                group->merge(templateGroup);
            }
        }
    };
}
