#pragma once

#include <memory>

#include "Spec/Types/SpecGroupResult.h"

namespace Spec::Types {
    class SpecResults {
        std::shared_ptr<SpecGroupResult> _rootResultGroup;

    public:
        SpecResults() : _rootResultGroup(std::make_shared<SpecGroupResult>()) {}

        std::shared_ptr<SpecGroupResult> GetRoot() { return _rootResultGroup; }
        void                             SetRoot(std::shared_ptr<SpecGroupResult> root) { _rootResultGroup = root; }

        unsigned int GetTotalTests() { return _rootResultGroup->GetTotalTests(); }
        unsigned int GetTotalPassed() { return _rootResultGroup->GetTotalPassed(); }
        unsigned int GetTotalFailed() { return _rootResultGroup->GetTotalFailed(); }
    };
}
