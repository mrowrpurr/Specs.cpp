#pragma once

#include "Specs/ISpecRunner.h"

namespace Specs::Runners {

    //! `Specs.cpp` default test runner (see also ParallelSpecRunner).
    class DefaultRunner : public ISpecRunner {};
}
