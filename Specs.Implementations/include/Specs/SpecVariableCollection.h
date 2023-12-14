#pragma once

#include <Specs/API.h>
#include <collections.h>

namespace SpecsCpp {

    class SpecVariableCollection : public ISpecVariableCollection {
        ISpecGroup*                                 _parent = nullptr;
        collections_map<std::string, IVoidPointer*> _variables;

    public:
        SpecVariableCollection(ISpecGroup* group = nullptr) : _parent(group) {}

        ~SpecVariableCollection() override { clear(); }

        void set(const char* name, IVoidPointer* variable) override { _variables[name] = variable; }

        bool exists(const char* name) const override {
            if (_variables.find(name) != _variables.end()) return true;
            if (_parent != nullptr) return _parent->has_var(name);
            return false;
        }

        IVoidPointer* get(const char* name) const override {
            auto found = _variables.find(name);
            if (found != _variables.end()) return found->second;
            if (_parent != nullptr) return _parent->var(name);
            return nullptr;
        }

        void foreach_variable(ForEachVariableFn* fn) const override {
            for (const auto& [name, variable] : _variables) fn->invoke(variable);
        }

        void clear() override {
            for (const auto& [name, variable] : _variables) delete variable;
            _variables.clear();
        }
    };
}
