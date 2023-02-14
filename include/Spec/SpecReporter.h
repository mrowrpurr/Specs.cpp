#pragma once

#include "Spec/SpecGroup.h"
#include "Spec/SpecTest.h"

namespace Spec {

    class SpecReporter {
    public:
        virtual void BeginTest(SpecTest& test) { throw "Not implemented"; }
        virtual void EndTest(SpecTest& test, bool passed, const std::string& failureMessage) {
            throw "Not implemented";
        }
        virtual void BeginGroup(SpecGroup& group) { throw "Not implemented"; }
        virtual void EndGroup(SpecGroup& group) { throw "Not implemented"; }
    };
}