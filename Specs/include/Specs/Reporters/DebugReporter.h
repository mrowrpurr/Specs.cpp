#pragma once

#include "Specs/ISpecReporter.h"

//! Test reporters.
namespace Specs::Reporters {

    //! `Specs.cpp` reporter that prints detailed output (useful for debugging `Specs.cpp`).
    class DebugReporter : public ISpecReporter {};
}