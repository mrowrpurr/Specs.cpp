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

        // TODO - replace the function<void()> code with a shared_ptr to a SpecTestResult
        //        and HandleException should take BOTH the exception_ptr and the SpecTestResult
        static bool RunAndHandleError(
            SpecTest& test, SpecTestResult& result,
            std::vector<std::shared_ptr<ISpecExceptionHandler>> exceptionHandlers
        ) {
            try {
                test.Run();
                // test.Pass(); <--- PROMISE, we're not even doing this yet!
                result.Pass();
                return true;
            } catch (...) {
                for (auto& handler : exceptionHandlers) {
                    if (handler->HandleException(std::current_exception(), result)) break;
                }
                result.Fail();
                // test.Fail(); <--- PROMISE, we're not even doing this yet!
                return false;
            }
        }
    };
}