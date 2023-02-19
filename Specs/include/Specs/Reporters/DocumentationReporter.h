#pragma once

#include "Specs/ISpecReporter.h"

namespace Specs::Reporters {

    //! `Specs.cpp` reporter which prints out indented test groups and test cases on individual lines.
    class DocumentationReporter : public ISpecReporter {};
}