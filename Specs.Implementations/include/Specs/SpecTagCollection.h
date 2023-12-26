#pragma once

#include <Specs/API.h>
#include <collections.h>

#include <string>

namespace SpecsCpp {

    class SpecTagCollection : public ISpecTagCollection {
        collections_set<std::string> _tags;

        void merge_foreach(const char* value) { add(value); }

        FunctionPointer<void(const char*)> _merge_foreach =
            function_pointer(this, &SpecTagCollection::merge_foreach);

    public:
        void add(const char* value) override { _tags.emplace(value); }
        bool has(const char* key) const override {
            auto found = _tags.find(key);
            return found != _tags.end();
        }
        void foreach_tag(ForEachTagFn* fn) const override {
            for (auto& tag : _tags) fn->invoke(tag.c_str());
        }
        void merge(ISpecTagCollection* other) override { other->foreach_tag(&_merge_foreach); }
        void clear() override { _tags.clear(); }
    };
}
