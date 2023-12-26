#pragma once

#include <Specs/API.h>

#include <string>
#include <vector>

namespace SpecsCpp {

    class SpecRunTextOptionList : public ISpecRunTextOptionList {
        std::vector<std::string> _textList;

    public:
        bool any() const override { return !_textList.empty(); }
        void add(const char* text) override { _textList.push_back(text); }
        void clear() override { _textList.clear(); }
        void foreach_option(ForEachOptionFn* fn) const override {
            for (const auto& text : _textList) fn->invoke(text.c_str());
        }
    };
}
