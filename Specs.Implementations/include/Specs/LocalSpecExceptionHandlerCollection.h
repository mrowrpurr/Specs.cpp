#pragma once

#include <Specs/API.h>

#include <deque>

namespace SpecsCpp {

    class LocalSpecExceptionHandlerCollection : public ILocalSpecExceptionHandlerCollection {
        std::deque<ILocalSpecExceptionHandler*> _handlers;

    public:
        void register_exception_handler(ILocalSpecExceptionHandler* handler) override {
            _handlers.push_front(handler);
        }

        void foreach_exception_handler(ForEachExceptionHandlerFn* fn) const override {
            for (const auto& handler : _handlers) fn->invoke(handler);
        }
    };
}
