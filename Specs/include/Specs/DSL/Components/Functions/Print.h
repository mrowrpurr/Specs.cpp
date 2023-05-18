#pragma once

#include <string_format.h>

#include <iostream>

namespace Specs::DSL::Components::Functions {

    // template <class... Args>
    // void Print(const std::string& text, Args&&... args) {
    //     std::cout << string_format(text, args...);
    // }
}

// Maybe just for MSVC or when using <format> because of how strict it is?
#define Print(...) std::cout << string_format(__VA_ARGS__) << std::endl
