#pragma once

#include <exception>

#include "Specs/ISpecExceptionHandler.h"
#include "Specs/SpecTestCaseResult.h"

//! Exception handlers for SpecTestCase.
namespace Specs::ExceptionHandlers {

    //! Handles generic exceptions thrown by SpecTestCase (e.g. `std::exception`, `const char*`, `std::string`)
    class FallbackExceptionHandler : public ISpecExceptionHandler {
    public:
        bool HandleException(std::exception_ptr exception, SpecTestCaseResult& testResult) override {
            try {
                std::rethrow_exception(exception);
            } catch (const std::exception& e) {
                testResult.SetFailureMessage(e.what());
            } catch (const char* e) {
                testResult.SetFailureMessage(e);
            } catch (const std::string& e) {
                testResult.SetFailureMessage(e);
            } catch (...) {
                testResult.SetFailureMessage("Unknown exception");
            }
            return true;
        }
    };
}