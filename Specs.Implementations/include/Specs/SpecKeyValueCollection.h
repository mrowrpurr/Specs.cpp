#pragma once

#include <Specs/API.h>
#include <collections.h>

#include <memory>
#include <string>

#include "SpecKeyValue.h"

namespace SpecsCpp {

    class SpecKeyValueCollection : public ISpecKeyValueCollection {
        collections_map<std::string, std::unique_ptr<SpecKeyValue>> _values;

    public:
        void add(const char* key, const char* value) override {
            _values[key] = std::make_unique<SpecKeyValue>(key, value);
        }

        bool has(const char* key) const override { return _values.contains(key); }

        const char* get(const char* key) const override {
            auto found = _values.find(key);
            if (found != _values.end()) return found->second.get()->value();
            return nullptr;
        }

        void foreach_metadata(ForEachMetaDataFn* fn) const override {
            for (const auto& [key, value] : _values) fn->invoke(value.get());
        }
    };
}
