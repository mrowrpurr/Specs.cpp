#pragma once

#include "Specs/ISpecReporter.h"

namespace Specs::Reporters {

    //! `Specs.cpp` reporter that prints detailed output (useful for debugging `Specs.cpp`).
    class DebugReporter : public ISpecReporter {};
}