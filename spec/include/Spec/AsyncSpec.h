#pragma once

#include <memory>

#include "Spec/SpecTest.h"

namespace Spec {

    class AsyncSpec {
        std::shared_ptr<SpecTest> _test;

    public:
        AsyncSpec(const std::shared_ptr<SpecTest>& test) : _test(test) {}

        void done(const std::string& message) {
            _test->GetPromise()->set_exception(
                std::make_exception_ptr(std::runtime_error(message))
            );
        }
        void done(const char* message) { done(std::string(message)); }
        void done(bool passed = true) { _test->GetPromise()->set_value(passed); }

        void tryCatch(std::function<void()> func) {
            try {
                func();
            } catch (...) {
                _test->GetPromise()->set_exception(std::current_exception());
            }
        }

        void background(std::function<void()> func) {
            std::thread t(func);
            t.detach();
        }
        void background(std::function<void(AsyncSpec&)> func) {
            std::thread t([func, this]() { func(*this); });
            t.detach();
        }
    };
}