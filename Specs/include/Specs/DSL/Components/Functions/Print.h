#pragma once

#include <format>
#include <iostream>

namespace Specs::DSL::Components::Functions {

    template <class... Args>
    void Print(const std::string_view text, Args&&... args) {
        std::cout << std::vformat(text, std::make_format_args(args...))
                  << std::endl;
    }
}