#pragma once

//! Exception handlers for SpecTestCase.
namespace Specs::ExceptionHandlers {

    //! Handles generic exceptions thrown by SpecTestCase (e.g. `std::exception`, `const char*`, `std::string`)
    class DefaultExceptionHandler {};
}