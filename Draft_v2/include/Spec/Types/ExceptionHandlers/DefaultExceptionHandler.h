#pragma once

#include <Spec/Types/ISpecExceptionHandler.h>

#include <exception>
#include <string>

namespace Spec::Types::ExceptionHandlers {

    class FallbackExceptionHandler : public ISpecExceptionHandler {
    public:
        bool HandleException(std::exception_ptr exception, SpecTestResult& result) {
            try {
                std::rethrow_exception(exception);
            } catch (const char* e) {
                result.SetFailure(e);
            } catch (std::string e) {
                result.SetFailure(e);
            } catch (std::exception& e) {
                result.SetFailure(e.what());
            } catch (...) {
                result.SetFailure("Unknown exception");
            }
            return true;
        }
    };

}