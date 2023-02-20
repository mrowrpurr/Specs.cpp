#pragma once

#include <functional>
#include <memory>

#include "Specs/ISpecExceptionHandler.h"

namespace Specs {

    class SpecExceptionHandlers {
        std::vector<std::shared_ptr<ISpecExceptionHandler>> _exceptionHandlers;

    public:
        static SpecExceptionHandlers& GetRegistry() {
            static SpecExceptionHandlers singleton;
            return singleton;
        }

        std::vector<std::shared_ptr<ISpecExceptionHandler>>& GetExceptionHandlers() { return _exceptionHandlers; }

        void RegisterExceptionHandler(std::shared_ptr<ISpecExceptionHandler> exceptionHandler) {
            _exceptionHandlers.insert(_exceptionHandlers.begin(), exceptionHandler);
        }
    };
}