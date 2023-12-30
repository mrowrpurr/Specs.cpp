#pragma once

#include <Specs/API.h>

#include <string>

namespace SpecsCpp {

    class SpecCommandLineOption : public ISpecCommandLineOption {
        std::string                                         _flags;
        std::string                                         _description;
        bool                                                _list;
        bool                                                _required;
        std::unique_ptr<VoidPointer<OnCommandLineOptionFn>> _option_callback = nullptr;

    public:
        SpecCommandLineOption(
            const char* flags, const char* description, bool list = false, bool required = false
        )
            : _flags(flags), _description(description), _list(list), _required(required) {}

        const char* flags() const override { return _flags.c_str(); }
        void        set_flags(const char* flags) override { _flags = flags; }

        const char* description() const override { return _description.c_str(); }
        void set_description(const char* description) override { _description = description; }

        bool is_list() const override { return _list; }
        void mark_list(bool list = true) override { _list = list; }

        bool is_required() const override { return _required; }
        void mark_required(bool required = true) override { _required = required; }

        OnCommandLineOptionFn* option_callback() const override {
            return _option_callback->as<OnCommandLineOptionFn*>();
        }
        void on_option(OnCommandLineOptionFn* fn, bool destructable = true) override {
            _option_callback = std::make_unique<VoidPointer<OnCommandLineOptionFn>>(fn);
            if (!destructable) _option_callback->delete_rule()->disable_destruct_on_delete();
        }
        void on_option(
            std::unique_ptr<IFunctionPointer<void(ISpecCommandLineOption*, ISpecApplication*)>> fn
        ) {
            _option_callback = std::make_unique<VoidPointer<OnCommandLineOptionFn>>(fn.release());
        }
    };
}
