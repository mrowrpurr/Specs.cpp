#pragma once

#include "Spec/SpecGroup.h"
#include "Spec/SpecTest.h"

namespace Spec::Types {
    class ISpecReporter {
    public:
        virtual void BeginTest(SpecTest& test)                                               = 0;
        virtual void EndTest(SpecTest& test, bool passed, const std::string& failureMessage) = 0;
        virtual void BeginGroup(SpecGroup& group)                                            = 0;
        virtual void EndGroup(SpecGroup& group)                                              = 0;
    };
}
