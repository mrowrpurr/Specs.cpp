#pragma once

#include <assert.hpp>

#ifdef NDEGUG
#include <string>
#include <vector>
#include <mutex>
#endif

namespace SpecsCpp::LibAssert {
    inline bool ShowStackTrace = false;

    #ifdef NDEBUG
    inline std::vector<std::string> AllAssertionFailureMessages;
    inline std::mutex AllAssertionFailureMessagesMutex;
    #endif
}

inline void libassert_specs_handler(
    libassert::assert_type type, ASSERTION fatal, const libassert::assertion_printer& printer
) {
    std::string message = printer(libassert::utility::terminal_width(120));
    if (!SpecsCpp::LibAssert::ShowStackTrace) {
        std::string::size_type stack_trace_start = message.find("\nStack trace:");
        if (stack_trace_start != std::string::npos) message.erase(stack_trace_start);
    }
    #ifdef NDEBUG
        // In release mode, the c_str() is lost unless we hold onto the string somewhere.
        // Here we just add it to a never-ending vector. Which is fine, whatever.
        std::lock_guard<std::mutex> lock(SpecsCpp::LibAssert::AllAssertionFailureMessagesMutex);
        SpecsCpp::LibAssert::AllAssertionFailureMessages.emplace_back(message);
        throw SpecsCpp::LibAssert::AllAssertionFailureMessages.back().c_str();
    #else
        throw message.c_str();
    #endif
}
