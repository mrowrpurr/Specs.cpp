#pragma once

#include <exception>

#include "Specs/SpecTestCaseResult.h"

namespace Specs {

    //! Interface for handlers for exceptions thrown by SpecTestCase.
    class ISpecExceptionHandler {
    public:
        virtual bool HandleException(std::exception_ptr exception, SpecTestCaseResult& testResult) = 0;
    };
}
