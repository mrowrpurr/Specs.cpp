#pragma once

#include <exception>

namespace Spec::Types {

    class ISpecExceptionHandler {
    public:
        virtual bool HandleException(std::exception_ptr exception) = 0;
    };
}