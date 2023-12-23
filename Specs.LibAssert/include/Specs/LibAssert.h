#pragma once

#include <assert.hpp>

namespace SpecsCpp::LibAssert {
    inline bool ShowStackTrace = false;
}

inline void libassert_specs_handler(
    libassert::assert_type type, ASSERTION fatal, const libassert::assertion_printer& printer
) {
    std::string message = printer(libassert::utility::terminal_width(120));
    if (!SpecsCpp::LibAssert::ShowStackTrace) {
        std::string::size_type stack_trace_start = message.find("\nStack trace:");
        if (stack_trace_start != std::string::npos) message.erase(stack_trace_start);
    }
    throw message.c_str();
}
