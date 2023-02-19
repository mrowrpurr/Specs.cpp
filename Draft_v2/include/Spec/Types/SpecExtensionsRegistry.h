#pragma once

#include <functional>
#include <memory>

#include "Spec/SpecTest.h"
#include "Spec/Types/ISpecExceptionHandler.h"
#include "Spec/Types/SpecTestResult.h"

namespace Spec::Types {

    class SpecExtensionsRegistry {
        std::vector<std::shared_ptr<ISpecExceptionHandler>> _exceptionHandlers;

        SpecExtensionsRegistry()                                         = default;
        ~SpecExtensionsRegistry()                                        = default;
        SpecExtensionsRegistry(const SpecExtensionsRegistry&)            = delete;
        SpecExtensionsRegistry(SpecExtensionsRegistry&&)                 = delete;
        SpecExtensionsRegistry& operator=(const SpecExtensionsRegistry&) = delete;
        SpecExtensionsRegistry& operator=(SpecExtensionsRegistry&&)      = delete;

    public:
        static SpecExtensionsRegistry& GetRegistry() {
            static SpecExtensionsRegistry singleton;
            return singleton;
        }

        std::vector<std::shared_ptr<ISpecExceptionHandler>>& GetExceptionHandlers() { return _exceptionHandlers; }

        void RegisterExceptionHandler(std::shared_ptr<ISpecExceptionHandler> exceptionHandler) {
            _exceptionHandlers.insert(_exceptionHandlers.begin(), exceptionHandler);
        }

        template <typename T>
        void RegisterExceptionHandler() {
            RegisterExceptionHandler(std::make_shared<T>());
        }

        static bool RunAndHandleError(
            std::shared_ptr<SpecTest> test, SpecTestResult& result,
            std::vector<std::shared_ptr<ISpecExceptionHandler>> exceptionHandlers
        ) {
            try {
                if (test->IsAsync()) {
                    std::future<bool> future;
                    if (!test->RunAndWait(future, std::chrono::seconds(3))) {
                        result.SetFailure("Async test timed out");
                        return false;
                    }
                    if (!future.get()) {
                        result.SetFailure("Async test failed");
                        return false;
                    }
                } else {
                    test->Run();
                }
                return true;
            } catch (...) {
                for (auto& handler : exceptionHandlers) {
                    if (handler->HandleException(std::current_exception(), result)) break;
                }
                result.Fail();
                return false;
            }
        }
    };
}