#pragma once

#include <Specs/API.h>
#include <string_format.h>

#include <string>
#include <string_view>

#include "SpecComponent.h"
#include "SpecDocumented.h"

namespace SpecsCpp {

    class SpecGroup : public ISpecGroup, public SpecComponent, public SpecDocumented {
        std::string _fullDescription;

        std::vector<ISpecGroup*>    _childGroups;
        std::vector<ISpec*>         _specs;
        std::vector<ISpecSetup*>    _setups;
        std::vector<ISpecTeardown*> _teardowns;

        void merge_child_groups(ISpecGroup* other) { add_group(other); }
        void merge_specs(ISpec* other) { add_spec(other); }
        void merge_setups(ISpecSetup* other) { add_setup(other); }
        void merge_teardowns(ISpecTeardown* other) { add_teardown(other); }

        FunctionPointer<void(ISpecGroup*)> _merge_child_groups_fn =
            function_pointer(this, &SpecGroup::merge_child_groups);
        FunctionPointer<void(ISpec*)> _merge_specs_fn =
            function_pointer(this, &SpecGroup::merge_specs);
        FunctionPointer<void(ISpecSetup*)> _merge_setups_fn =
            function_pointer(this, &SpecGroup::merge_setups);
        FunctionPointer<void(ISpecTeardown*)> _merge_teardowns_fn =
            function_pointer(this, &SpecGroup::merge_teardowns);

    public:
        SpecGroup(ISpecGroup* parent = nullptr, std::string_view description = "")
            : SpecComponent(SpecComponentType::Group, parent), SpecDocumented(description) {
            if (parent == nullptr || !parent->full_description()) _fullDescription = description;
            else
                _fullDescription =
                    string_format("{} > {}", parent->full_description(), description);
        }

        std::vector<ISpecGroup*>&    groups() { return _childGroups; }
        std::vector<ISpec*>&         specs() { return _specs; }
        std::vector<ISpecSetup*>&    Setups() { return _setups; }
        std::vector<ISpecTeardown*>& Teardowns() { return _teardowns; }

        void foreach_group(ForEachGroupFn* callback) const override {
            for (auto* group : _childGroups) callback->invoke(group);
        }

        void foreach_spec(ForEachSpecFn* callback) const override {
            for (auto* spec : _specs) callback->invoke(spec);
        }

        void foreach_setup(ForEachSetupFn* callback) const override {
            for (auto* Setup : _setups) callback->invoke(Setup);
        }

        void foreach_teardown(ForEachTeardownFn* callback) const override {
            for (auto* Teardown : _teardowns) callback->invoke(Teardown);
        }

        void add_group(ISpecGroup* group) override { _childGroups.push_back(group); }
        void add_spec(ISpec* spec) override { _specs.push_back(spec); }
        void add_setup(ISpecSetup* Setup) override { _setups.push_back(Setup); }
        void add_teardown(ISpecTeardown* Teardown) override { _teardowns.push_back(Teardown); }

        const char* full_description() const override {
            return _fullDescription.empty() ? nullptr : _fullDescription.c_str();
        }

        void merge(ISpecGroup* other) override {
            other->foreach_group(&_merge_child_groups_fn);
            other->foreach_spec(&_merge_specs_fn);
            other->foreach_setup(&_merge_setups_fn);
            other->foreach_teardown(&_merge_teardowns_fn);
        }
    };
}
