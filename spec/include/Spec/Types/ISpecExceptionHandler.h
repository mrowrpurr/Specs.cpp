#pragma once

#include <exception>

#include "Spec/Types/SpecTestResult.h"

namespace Spec::Types {

    class ISpecExceptionHandler {
    public:
        virtual bool HandleException(std::exception_ptr exception, SpecTestResult& result) = 0;
    };
}