#pragma once

#include "Spec/Internal/Macros/FunctionRunner.h"
#include "Spec/Types/ExceptionHandlers/SnowhouseExceptionHandler.h"

namespace {
    Spec::Internal::FunctionRunner RegisterSnowhouseExceptionHandler{
        []() { Spec::Types::ExceptionHandlers::SnowhouseExceptionHandler::Register(); }};
}