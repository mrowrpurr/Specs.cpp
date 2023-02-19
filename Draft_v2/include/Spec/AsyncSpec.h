#pragma once

#include <memory>

#include "Spec/SpecTest.h"

namespace Specs {

    class AsyncSpec : public std::enable_shared_from_this<AsyncSpec> {
        std::shared_ptr<SpecTest> _test;

    public:
        AsyncSpec(const std::shared_ptr<SpecTest>& test) : _test(test) {}

        void done(const std::string& message) { _test->Fail(message); }
        void done(const char* message) { done(std::string(message)); }
        void done(bool passed = true) {
            if (passed)
                _test->Pass();
            else
                _test->Fail();
        }
        void error(const std::string& message) { done(message); }

        void tryCatch(std::function<void()> func) {
            try {
                func();
            } catch (...) {
                _test->Fail(std::current_exception());
            }
        }

        void background(std::function<void()> func) {
            // TODO use tryCatch
            std::thread t(func);
            t.detach();
        }
        void background(std::function<void(std::function<void()>)> func) {
            // TODO use tryCatch
            std::thread t([func, this]() { func([this]() { done(); }); });
            t.detach();
        }
        void background(std::function<void(std::shared_ptr<AsyncSpec>)> func) {
            auto        ptr = shared_from_this();
            std::thread t([func, ptr]() {
                ptr->tryCatch([func, ptr]() { func(ptr); });
            });
            t.detach();
        }
    };
}