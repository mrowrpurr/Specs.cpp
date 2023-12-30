#pragma once

#include <Specs/API.h>
#include <string_format.h>

#include <string>
#include <string_view>

#include "SpecComponent.h"
#include "SpecDocumented.h"
#include "SpecVariableCollection.h"

namespace SpecsCpp {

    class SpecGroup : public ISpecGroup, public SpecComponent, public SpecDocumented {
        std::string _fullDescription;

        std::vector<ISpecGroup*>    _childGroups;
        std::vector<ISpec*>         _specs;
        std::vector<ISpecSetup*>    _setups;
        std::vector<ISpecTeardown*> _teardowns;
        std::vector<ISpecSetup*>    _oneTimeSetups;
        std::vector<ISpecTeardown*> _oneTimeTeardowns;

        std::unique_ptr<SpecVariableCollection> _variables;

        void merge_child_groups(ISpecGroup* other) { add_group(other); }
        void merge_tests(ISpec* other) { add_test(other); }
        void merge_setups(ISpecSetup* other) { add_setup(other); }
        void merge_teardowns(ISpecTeardown* other) { add_teardown(other); }
        void merge_one_time_setups(ISpecSetup* other) { add_one_time_setup(other); }
        void merge_one_time_teardowns(ISpecTeardown* other) { add_one_time_teardown(other); }

        FunctionPointer<void(ISpecGroup*)> _merge_child_groups_fn =
            function_pointer(this, &SpecGroup::merge_child_groups);
        FunctionPointer<void(ISpec*)> _merge_tests_fn =
            function_pointer(this, &SpecGroup::merge_tests);
        FunctionPointer<void(ISpecSetup*)> _merge_setups_fn =
            function_pointer(this, &SpecGroup::merge_setups);
        FunctionPointer<void(ISpecTeardown*)> _merge_teardowns_fn =
            function_pointer(this, &SpecGroup::merge_teardowns);
        FunctionPointer<void(ISpecSetup*)> _merge_one_time_setups_fn =
            function_pointer(this, &SpecGroup::merge_one_time_setups);
        FunctionPointer<void(ISpecTeardown*)> _merge_one_time_teardowns_fn =
            function_pointer(this, &SpecGroup::merge_one_time_teardowns);

    public:
        SpecGroup(ISpecGroup* parent = nullptr, std::string_view description = "")
            : SpecComponent(SpecComponentType::Group, parent),
              SpecDocumented(description),
              _variables(std::make_unique<SpecVariableCollection>(parent)) {
            if (parent == nullptr || strlen(parent->full_description()) == 0)
                _fullDescription = description;
            else
                _fullDescription =
                    string_format("{} > {}", parent->full_description(), description);
        }

        SpecGroup(std::string_view description) : SpecGroup(nullptr, description) {}

        void foreach_group(ForEachGroupFn* callback) const override {
            for (auto* group : _childGroups) callback->invoke(group);
        }

        void foreach_test(ForEachSpecFn* callback) const override {
            for (auto* spec : _specs) callback->invoke(spec);
        }

        void foreach_setup(ForEachSetupFn* callback) const override {
            for (auto* setup : _setups) callback->invoke(setup);
        }

        void foreach_teardown(ForEachTeardownFn* callback) const override {
            for (auto* teardown : _teardowns) callback->invoke(teardown);
        }

        void foreach_one_time_setup(ForEachSetupFn* callback) const override {
            for (auto* setup : _oneTimeSetups) callback->invoke(setup);
        }

        void foreach_one_time_teardown(ForEachTeardownFn* callback) const override {
            for (auto* teardown : _oneTimeTeardowns) callback->invoke(teardown);
        }

        void add_group(ISpecGroup* group) override { _childGroups.push_back(group); }
        void add_test(ISpec* spec) override { _specs.push_back(spec); }
        void add_setup(ISpecSetup* setup) override { _setups.push_back(setup); }
        void add_teardown(ISpecTeardown* teardown) override { _teardowns.push_back(teardown); }
        void add_one_time_setup(ISpecSetup* setup) override { _oneTimeSetups.push_back(setup); }
        void add_one_time_teardown(ISpecTeardown* teardown) override {
            _oneTimeTeardowns.push_back(teardown);
        }

        const char* full_description() const override { return _fullDescription.c_str(); }

        void merge(ISpecGroup* other) override {
            other->foreach_group(&_merge_child_groups_fn);
            other->foreach_test(&_merge_tests_fn);
            other->foreach_setup(&_merge_setups_fn);
            other->foreach_teardown(&_merge_teardowns_fn);
            other->foreach_one_time_setup(&_merge_one_time_setups_fn);
            other->foreach_one_time_teardown(&_merge_one_time_teardowns_fn);
        }

        ISpecVariableCollection* variables() const override { return _variables.get(); }
    };
}
