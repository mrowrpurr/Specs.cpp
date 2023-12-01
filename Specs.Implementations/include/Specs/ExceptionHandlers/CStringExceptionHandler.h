#pragma once

#include <Specs/API.h>
#include <_Log_.h>

#include "../SpecExceptionMessage.h"

namespace SpecsCpp::ExceptionHandlers {

    class CStringExceptionHandler : public ILocalSpecExceptionHandler {
    public:
        bool handle_exception(
            std::exception_ptr*                         exception,
            LocalSpecExceptionFailureMessageCallbackFn* failureMessageCallback
        ) override {
            try {
                std::rethrow_exception(*exception);
            } catch (const char* exceptionMessage) {
                if (failureMessageCallback) {
                    SpecExceptionMessage failureMessage{exceptionMessage};
                    failureMessageCallback->invoke(&failureMessage);
                }
                return true;
            } catch (...) {
                return false;
            }
        }
    };
}