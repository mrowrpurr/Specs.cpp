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
        std::vector<ISpecGroup*> _savedGroupStack;

        ISpecGroup* _currentFileGroup     = nullptr;
        ISpecGroup* _savedFileGroup       = nullptr;
        ISpecGroup* _currentTopLevelGroup = nullptr;
        ISpecGroup* _savedTopLevelGroup   = nullptr;

        // A place to store some memory! These go here and never leave :)
        std::vector<std::unique_ptr<SpecTest>>     _registeredSpecs;
        std::vector<std::unique_ptr<SpecSetup>>    _registeredsetups;
        std::vector<std::unique_ptr<SpecTeardown>> _registeredteardowns;
        std::vector<std::unique_ptr<SpecGroup>>    _registeredGroups;
        std::vector<std::unique_ptr<SpecSetup>>    _registeredOneTimesetups;
        std::vector<std::unique_ptr<SpecTeardown>> _registeredOneTimeteardowns;

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

        void clear_group_stack() {
            _currentGroupStack.clear();

            // This makes the current group / file notes no longer valid
            _currentFileGroup     = nullptr;
            _currentTopLevelGroup = nullptr;
        }

        void reset_group_stack() {
            clear_group_stack();
            if (auto* rootGroup = root()) push(rootGroup);
        }

        void save_group_stack() {
            _savedFileGroup     = _currentFileGroup;
            _savedTopLevelGroup = _currentTopLevelGroup;
            _savedGroupStack    = _currentGroupStack;
        }

        void restore_group_stack() {
            _currentFileGroup     = _savedFileGroup;
            _currentTopLevelGroup = _savedTopLevelGroup;
            _currentGroupStack    = _savedGroupStack;
        }

        void define_template(
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

        void define_group(std::string_view description, std::unique_ptr<SpecCodeBlock> codeBlock) {
            if (auto* group = get()) {
                auto  specGroup    = std::make_unique<SpecGroup>(get(), description);
                auto* specGroupPtr = specGroup.get();
                _registeredGroups.push_back(std::move(specGroup));
                group->add_group(_registeredGroups.back().get());

                // Evaluate the group block (with this group being the 'current group')
                push(specGroupPtr);
                codeBlock->run(specGroupPtr, nullptr, nullptr);
                pop();
            } else {
                _Log_("define_group() called but no group is active!");
            }
        }

        void define_spec(std::string_view description, std::unique_ptr<SpecCodeBlock> codeBlock) {
            if (auto* group = get()) {
                auto  spec = std::make_unique<SpecTest>(get(), description, std::move(codeBlock));
                auto* specPtr = spec.get();
                _registeredSpecs.push_back(std::move(spec));
                group->add_spec(specPtr);
            } else {
                _Log_("define_spec() called but no group is active!");
            }
        }

        void define_setup(std::unique_ptr<SpecCodeBlock> codeBlock) {
            if (auto* group = get()) {
                auto  setup    = std::make_unique<SpecSetup>(get(), std::move(codeBlock));
                auto* setupPtr = setup.get();
                _registeredsetups.push_back(std::move(setup));
                group->add_setup(setupPtr);
            }
        }

        void define_teardown(std::unique_ptr<SpecCodeBlock> codeBlock) {
            if (auto* group = get()) {
                auto  teardown    = std::make_unique<SpecTeardown>(get(), std::move(codeBlock));
                auto* teardownPtr = teardown.get();
                _registeredteardowns.push_back(std::move(teardown));
                group->add_teardown(teardownPtr);
            }
        }

        void define_one_time_setup(std::unique_ptr<SpecCodeBlock> codeBlock) {
            if (auto* group = get()) {
                auto  setup    = std::make_unique<SpecSetup>(get(), std::move(codeBlock));
                auto* setupPtr = setup.get();
                _registeredOneTimesetups.push_back(std::move(setup));
                group->add_one_time_setup(setupPtr);
            }
        }

        void define_one_time_teardown(std::unique_ptr<SpecCodeBlock> codeBlock) {
            if (auto* group = get()) {
                auto  teardown    = std::make_unique<SpecTeardown>(get(), std::move(codeBlock));
                auto* teardownPtr = teardown.get();
                _registeredOneTimeteardowns.push_back(std::move(teardown));
                group->add_one_time_teardown(teardownPtr);
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

        void declare_top_level_group(std::string_view description) {
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

        void clear_file_group() {
            if (auto* group = get()) {
                // Is there another top-level group? Let's pop it off
                if (_currentFileGroup) {
                    while (get() != _currentFileGroup) pop();
                    if (get() == _currentFileGroup) pop();
                }
                _currentFileGroup = nullptr;
            }
        }

        void declare_file_group(std::string_view description, bool removeUnderscores = true) {
            clear_top_level_group();
            clear_file_group();

            if (auto* group = get()) {
                std::string descriptionText{description};
                if (removeUnderscores) {
                    std::replace(descriptionText.begin(), descriptionText.end(), '_', ' ');
                    description = descriptionText;
                }
                auto  specGroup    = std::make_unique<SpecGroup>(get(), descriptionText);
                auto* specGroupPtr = specGroup.get();
                _currentFileGroup  = specGroupPtr;
                _registeredGroups.push_back(std::move(specGroup));
                group->add_group(specGroupPtr);
                push(specGroupPtr);
            }
        }

        void declare_top_level_template(
            std::string_view templateName, bool clearFileGroup = false
        ) {
            clear_top_level_group();
            if (clearFileGroup) clear_file_group();

            if (auto* group = get()) {
                auto foundExisting = _testTemplateGroups.find(templateName.data());
                if (foundExisting != _testTemplateGroups.end()) {
                    clear_group_stack();  // The top-level things should NOT be registered anywhere
                } else {
                    auto  specGroup       = std::make_unique<SpecGroup>(get(), templateName);
                    auto* specGroupPtr    = specGroup.get();
                    _currentTopLevelGroup = specGroupPtr;
                    _testTemplateGroups[templateName.data()] = std::move(specGroup);
                    push(specGroupPtr);
                }
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

        void use_templates(std::vector<std::string_view> templateNames) {
            if (auto* group = get())
                for (auto& templateName : templateNames) use_template(templateName);
        }

        // TODO: functions needed for Tag(x) and Data(x, y) and MetaData({}, {})
    };
}
