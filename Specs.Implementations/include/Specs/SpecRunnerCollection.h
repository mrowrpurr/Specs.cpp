#pragma once

#include <Specs/API.h>
#include <collections.h>

#include <string>


namespace SpecsCpp {

    class SpecRunnerCollection : public ISpecRunnerCollection {
        collections_map<std::string, ISpecRunner*> _runners;

    public:
        void add(const char* name, ISpecRunner* runner) override { _runners[name] = runner; }

        bool has(const char* name) const override { return _runners.contains(name); }

        ISpecRunner* get(const char* name) const override {
            auto found = _runners.find(name);
            if (found != _runners.end()) return found->second;
            return nullptr;
        }

        void foreach_runner(ForEachRunnerFn* fn) const override {
            for (const auto& [name, runner] : _runners) fn->invoke(runner);
        }
    };
}
