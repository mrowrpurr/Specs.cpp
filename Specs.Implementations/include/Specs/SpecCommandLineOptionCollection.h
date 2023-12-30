#pragma once

#include <Specs/API.h>

#include <vector>

namespace SpecsCpp {

    class SpecCommandLineOptionCollection : public ISpecCommandLineOptionCollection {
        std::vector<std::unique_ptr<VoidPointer<ISpecCommandLineOption>>> _options;

    public:
        void add(ISpecCommandLineOption* option, bool destructable = true) override {
            auto option_ptr = std::make_unique<VoidPointer<ISpecCommandLineOption>>(option);
            if (!destructable) option_ptr->delete_rule()->disable_destruct_on_delete();
            _options.emplace_back(std::move(option_ptr));
        }

        ISpecCommandLineOption* get_at(std::uint32_t index) const override {
            return _options[index]->as<ISpecCommandLineOption*>();
        }

        std::uint32_t count() const override { return _options.size(); }

        void clear() override { _options.clear(); }

        void foreach_option(ForEachOptionFn* fn) const override {
            for (auto& option : _options) fn->invoke(option->as<ISpecCommandLineOption*>());
        }
    };
}
