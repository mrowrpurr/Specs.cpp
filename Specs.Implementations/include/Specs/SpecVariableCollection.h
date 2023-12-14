#pragma once

#include <Specs/API.h>
#include <collections.h>

namespace SpecsCpp {

    class SpecVariableCollection : public ISpecVariableCollection {
        collections_map<std::string, IVoidPointer*> _variables;

    public:
        void set(const char* name, IVoidPointer* variable) override { _variables[name] = variable; }

        bool exists(const char* name) const override { return _variables.contains(name); }

        IVoidPointer* get(const char* name) const override {
            auto found = _variables.find(name);
            if (found != _variables.end()) return found->second;
            return nullptr;
        }

        void foreach_variable(ForEachVariableFn* fn) const override {
            for (const auto& [name, variable] : _variables) fn->invoke(variable);
        }
    };
}
