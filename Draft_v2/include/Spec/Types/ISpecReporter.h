#pragma once

#include "Spec/SpecGroup.h"
#include "Spec/SpecTest.h"
#include "Spec/Types/SpecGroupResult.h"
#include "Spec/Types/SpecTestResult.h"

namespace Spec::Types {
    class ISpecReporter {
    public:
        virtual void BeginTest(std::shared_ptr<SpecTest> test, SpecTestResult& result)         = 0;
        virtual void EndTest(std::shared_ptr<SpecTest> test, SpecTestResult& result)           = 0;
        virtual void BeginSetup(std::shared_ptr<SpecTest> setup, SpecTestResult& result)       = 0;
        virtual void EndSetup(std::shared_ptr<SpecTest> setup, SpecTestResult& result)         = 0;
        virtual void BeginTeardown(std::shared_ptr<SpecTest> teardown, SpecTestResult& result) = 0;
        virtual void EndTeardown(std::shared_ptr<SpecTest> teardown, SpecTestResult& result)   = 0;
        virtual void BeginGroup(SpecGroup& group, SpecGroupResult& result)                     = 0;
        virtual void EndGroup(SpecGroup& group, SpecGroupResult& result)                       = 0;
    };
}
