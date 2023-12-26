#pragma once

#include <Specs/API.h>

#include "SpecDataValueCollection.h"
#include "SpecRunTextOptionList.h"

namespace SpecsCpp {

    class SpecRunOptions : public ISpecRunOptions {
        bool                     _list_only          = false;
        std::uint32_t            _default_timeout_ms = 5000;  // Default timeout is 5 seconds
        SpecRunTextOptionList    _name_matchers;
        SpecRunTextOptionList    _test_name_matchers;
        SpecRunTextOptionList    _group_name_matchers;
        SpecRunTextOptionList    _regex_name_matchers;
        SpecRunTextOptionList    _regex_test_name_matchers;
        SpecRunTextOptionList    _regex_group_name_matchers;
        SpecRunTextOptionList    _include_tags;
        SpecRunTextOptionList    _exclude_tags;
        SpecDataValueCollection  _data;
        SpecRunTextOptionList*   _name_matchers_ptr             = &_name_matchers;
        SpecRunTextOptionList*   _test_name_matchers_ptr        = &_test_name_matchers;
        SpecRunTextOptionList*   _group_name_matchers_ptr       = &_group_name_matchers;
        SpecRunTextOptionList*   _regex_name_matchers_ptr       = &_regex_name_matchers;
        SpecRunTextOptionList*   _regex_test_name_matchers_ptr  = &_regex_test_name_matchers;
        SpecRunTextOptionList*   _regex_group_name_matchers_ptr = &_regex_group_name_matchers;
        SpecRunTextOptionList*   _include_tags_ptr              = &_include_tags;
        SpecRunTextOptionList*   _exclude_tags_ptr              = &_exclude_tags;
        SpecDataValueCollection* _data_ptr                      = &_data;

    public:
        bool          list_only() const override { return _list_only; }
        void          list_only(bool value) override { _list_only = value; }
        std::uint32_t default_timeout_ms() const override { return _default_timeout_ms; }
        void          default_timeout_ms(std::uint32_t timeout_ms) override {
            _default_timeout_ms = timeout_ms;
        }
        ISpecRunTextOptionList* name_matchers() const override { return _name_matchers_ptr; }
        ISpecRunTextOptionList* test_name_matchers() const override {
            return _test_name_matchers_ptr;
        }
        ISpecRunTextOptionList* group_name_matchers() const override {
            return _group_name_matchers_ptr;
        }
        ISpecRunTextOptionList* regex_name_matchers() const override {
            return _regex_name_matchers_ptr;
        }
        ISpecRunTextOptionList* regex_test_name_matchers() const override {
            return _regex_test_name_matchers_ptr;
        }
        ISpecRunTextOptionList* regex_group_name_matchers() const override {
            return _regex_group_name_matchers_ptr;
        }
        ISpecRunTextOptionList*   include_tags() const override { return _include_tags_ptr; }
        ISpecRunTextOptionList*   exclude_tags() const override { return _exclude_tags_ptr; }
        ISpecDataValueCollection* data() const override { return _data_ptr; }
    };
}
