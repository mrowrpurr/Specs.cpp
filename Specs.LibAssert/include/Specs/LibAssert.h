#pragma once

#include <assert.hpp>

inline void libassert_specs_handler(
    libassert::assert_type type, ASSERTION fatal, const libassert::assertion_printer& printer
) {
    std::string message = printer(libassert::utility::terminal_width(120));
    throw message.c_str();
}
