#pragma once

#include "Specs/ISpecReporter.h"

namespace Specs::Reporters {

    //! `Specs.cpp` reporter which prints out a single line per test case.
    class OneLineReporter : public ISpecReporter {};
}