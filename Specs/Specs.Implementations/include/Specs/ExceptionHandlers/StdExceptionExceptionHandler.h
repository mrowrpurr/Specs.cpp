#pragma once

#include <Specs/API.h>

#include "../SpecExceptionMessage.h"

namespace SpecsCpp::ExceptionHandlers {

    class StdExceptionExceptionHandler : public ILocalSpecExceptionHandler {
    public:
        bool handle_exception(
            std::exception_ptr*                         exception,
            LocalSpecExceptionFailureMessageCallbackFn* failureMessageCallback
        ) override {
            try {
                std::rethrow_exception(*exception);
            } catch (const std::exception& e) {
                if (failureMessageCallback) {
                    SpecExceptionMessage failureMessage{e.what()};
                    failureMessageCallback->invoke(&failureMessage);
                }
                return true;
            } catch (...) {
                return false;
            }
        }
    };
}