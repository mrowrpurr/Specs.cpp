#pragma once

#include <functional>
#include <memory>

#include "Spec/Types/ISpecExceptionHandler.h"

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

        static void RunAndHandleError(
            std::function<void()> code, std::vector<std::shared_ptr<ISpecExceptionHandler>> exceptionHandlers
        ) {
            try {
                code();
            } catch (...) {
                Print("Trying {} exception handlers", exceptionHandlers.size());
                for (auto& handler : exceptionHandlers) {
                    if (handler->HandleException(std::current_exception())) return;
                }
                Print("Nothing handled it!!!");
            }
        }
    };
}