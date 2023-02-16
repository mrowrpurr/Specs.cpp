#pragma once

#include <Spec/Types/ISpecExceptionHandler.h>

#include <exception>
#include <string>

namespace Spec::Types::ExceptionHandlers {

    class DefaultExceptionHandler : public ISpecExceptionHandler {
    public:
        bool HandleException(std::exception_ptr exception) {
            Print("I AM DEFAULT EXCEPTION HANDLER!");
            try {
                std::rethrow_exception(exception);
            } catch (const char* e) {
                Print("DefaultExceptionHandler: Caught char* exception: {}", e);
            } catch (std::string e) {
                Print("DefaultExceptionHandler: Caught std::string exception: {}", e);
            } catch (std::exception& e) {
                Print("DefaultExceptionHandler: Caught std::exception: {}", e.what());
            } catch (...) {
                Print("DefaultExceptionHandler: Caught unknown exception");
            }
        }
    };

}