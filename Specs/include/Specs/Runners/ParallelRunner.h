#pragma once

#include "Specs/ISpecRunner.h"

namespace Specs::Runners {

    //! `Specs.cpp` test runner that runs tests in parallel (see also SpecRunner).
    class ParallelRunner : public ISpecRunner {};
}
