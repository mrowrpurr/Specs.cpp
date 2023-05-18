#pragma once

#include <string_format.h>

#include <iostream>

namespace Specs::DSL::Components::Functions {

    template <class... Args>
    void Print(const std::string_view text, Args&&... args) {
        std::cout << string_format(text, args...);
    }
}