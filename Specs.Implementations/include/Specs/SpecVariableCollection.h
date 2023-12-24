#pragma once

#include <Specs/API.h>
#include <collections.h>

namespace SpecsCpp {

    class SpecVariableCollection : public ISpecVariableCollection {
        ISpecGroup*                                 _parent = nullptr;
        collections_map<std::string, IVoidPointer*> _variables;
        collections_map<std::string, bool>          _destructable;

    public:
        SpecVariableCollection(ISpecGroup* group = nullptr) : _parent(group) {}

        ~SpecVariableCollection() override { clear(); }

        void set(const char* name, IVoidPointer* variable, bool destructable = true) override {
            variable->delete_rule()->set_destruct_on_delete(destructable);
            _variables[name] = variable;
        }

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

        bool is_destructable(const char* name) const override {
            if (auto* voidPtr = get(name)) return voidPtr->delete_rule()->destruct_on_delete();
            return false;
        }

        void foreach_variable(ForEachVariableFn* fn) const override {
            for (const auto& [name, variable] : _variables) fn->invoke(variable);
        }

        void clear() override { _variables.clear(); }

        void unset(const char* name) override {
            auto found = _variables.find(name);
            if (found != _variables.end()) _variables.erase(found);
        }

        void delete_var(const char* name) override {
            auto found = _variables.find(name);
            if (found != _variables.end()) {
                delete found->second;
                _variables.erase(found);
            }
        }

        void delete_all() override {
            for (const auto& [name, variable] : _variables) delete variable;
            _variables.clear();
        }
    };
}
