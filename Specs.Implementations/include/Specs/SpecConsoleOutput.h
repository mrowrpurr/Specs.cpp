#pragma once

#include <Specs/API.h>

#include <iostream>

namespace SpecsCpp {

    class SpecConsoleOutput : public ISpecOutput {
    public:
        void write(const char* text) override { std::cout << text << std::flush; }
    };
}
