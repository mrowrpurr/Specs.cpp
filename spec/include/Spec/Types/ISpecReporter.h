#pragma once

#include "Spec/SpecGroup.h"
#include "Spec/SpecTest.h"
#include "Spec/Types/SpecGroupResult.h"
#include "Spec/Types/SpecTestResult.h"

namespace Spec::Types {
    class ISpecReporter {
    public:
        virtual void BeginTest(SpecTest& test, SpecTestResult& result)     = 0;
        virtual void EndTest(SpecTest& test, SpecTestResult& result)       = 0;
        virtual void BeginGroup(SpecGroup& group, SpecGroupResult& result) = 0;
        virtual void EndGroup(SpecGroup& group, SpecGroupResult& result)   = 0;
    };
}
