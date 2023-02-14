#pragma once

#include "Spec/SpecResultGroup.h"
#include "Spec/SpecResultsSummary.h"
#include "SpecGroup.h"
#include "SpecTest.h"

namespace Spec {
    class SpecResults {
        SpecResultsSummary _summary;
        SpecResultGroup    _rootGroup;

    public:
        SpecResultsSummary& GetSummary() { return _summary; }
        SpecResultGroup&    GetRootGroup() { return _rootGroup; }

        void BeginTest(SpecTest& test) {}
        void EndTest(SpecTest& test, bool passed, const std::string& failureMessage) {}
        void BeginGroup(SpecGroup& group) {}
        void EndGroup(SpecGroup& group) {}
    };
}
