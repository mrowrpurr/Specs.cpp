#pragma once

#include <Specs/API.h>

namespace SpecsCpp {

    class SpecConsoleOutput : public ISpecOutput {
    public:
        void write(const char* text) override {}
    };
}
