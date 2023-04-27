#pragma once

#include <snowhouse/snowhouse.h>

#include <exception>
#include <format>

#include "Specs/ISpecExceptionHandler.h"
#include "Specs/SpecTestCaseResult.h"

namespace Specs::ExceptionHandlers {

    //! Exception handler for assertions provided by the `Snowhouse` library.
    class SnowhouseExceptionHandler : public ISpecExceptionHandler {
        bool HandleException(std::exception_ptr exception, SpecTestCaseResult& testResult) override {
            try {
                std::rethrow_exception(exception);
            } catch (const snowhouse::AssertionException& e) {
                testResult.SetFailureMessage(std::format("[{}:{}] {}", e.file(), e.line(), e.what()));
                return true;
            } catch (...) {
                return false;
            }
        }
    };
}
