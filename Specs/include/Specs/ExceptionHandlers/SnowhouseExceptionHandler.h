#pragma once

#include <snowhouse/snowhouse.h>
#include <string_format.h>

#include <exception>

#include "../ISpecExceptionHandler.h"
#include "../SpecTestCaseResult.h"

namespace Specs::ExceptionHandlers {

    //! Exception handler for assertions provided by the `Snowhouse` library.
    class SnowhouseExceptionHandler : public ISpecExceptionHandler {
        bool HandleException(std::exception_ptr exception, SpecTestCaseResult& testResult) override {
            try {
                std::rethrow_exception(exception);
            } catch (const snowhouse::AssertionException& e) {
                testResult.SetFailureMessage(string_format("[{}:{}] {}", e.file(), e.line(), e.what()));
                return true;
            } catch (...) {
                return false;
            }
        }
    };
}
