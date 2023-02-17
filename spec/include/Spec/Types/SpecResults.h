#pragma once

#include <memory>

#include "Spec/Types/SpecGroupResult.h"

namespace Spec::Types {
    class SpecResults {
        std::shared_ptr<SpecGroupResult> _rootResultGroup;
        unsigned int                     _totalTests  = 0;
        unsigned int                     _totalPassed = 0;
        unsigned int                     _totalFailed = 0;

    public:
        SpecResults() : _rootResultGroup(std::make_shared<SpecGroupResult>()) {}

        std::shared_ptr<SpecGroupResult> GetRoot() { return _rootResultGroup; }
        void                             SetRoot(std::shared_ptr<SpecGroupResult> root) { _rootResultGroup = root; }

        unsigned int GetTotalTests() { return _totalTests; }
        void         IncrementTotalTests() { _totalTests++; }

        unsigned int GetTotalPassed() { return _totalPassed; }
        void         IncrementTotalPassed() { _totalPassed++; }

        unsigned int GetTotalFailed() { return _totalFailed; }
        void         IncrementTotalFailed() { _totalFailed++; }
    };
}
