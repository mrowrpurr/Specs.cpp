#pragma once

#include <Specs/API.h>
#include <collections.h>

#include <string>

namespace SpecsCpp {

    class SpecDataValueCollection : public ISpecDataValueCollection {
        collections_map<std::string, ISpecDataValue*> _values;

        void merge_foreach(ISpecDataValue* value) { add(value); }

        FunctionPointer<void(ISpecDataValue*)> _merge_foreach =
            function_pointer(this, &SpecDataValueCollection::merge_foreach);

    public:
        ~SpecDataValueCollection() override {
            for (auto& [key, value] : _values) delete value;
        }

        void add(ISpecDataValue* value) override { _values.emplace(value->key(), value); }
        ISpecDataValue* get(const char* key) const override {
            auto found = _values.find(key);
            return found == _values.end() ? nullptr : found->second;
        }
        bool has(const char* key) const override {
            auto found = _values.find(key);
            return found != _values.end();
        }
        void foreach(ForEachSpecDataFn* fn) const override {
            for (auto& [key, value] : _values) fn->invoke(value);
        }
        void merge(ISpecDataValueCollection* other) override { other->foreach(&_merge_foreach); }
        void clear() override { _values.clear(); }
    };
}
