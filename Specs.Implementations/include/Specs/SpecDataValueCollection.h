#pragma once

#include <Specs/API.h>
#include <collections.h>

#include <string>

namespace SpecsCpp {

    class SpecDataValueCollection : public ISpecDataValueCollection {
        collections_map<std::string, ISpecDataValue*> _values;

    public:
        void add(ISpecDataValue* value) override { _values.emplace(value->key(), value); }
        ISpecDataValue* get(const char* key) const override {
            auto found = _values.find(key);
            return found == _values.end() ? nullptr : found->second;
        }
        bool has(const char* key) const override { return _values.contains(key); }
        void foreach(ForEachSpecDataFn* fn) const override {
            for (auto& [key, value] : _values) fn->invoke(value);
        }
    };
}
