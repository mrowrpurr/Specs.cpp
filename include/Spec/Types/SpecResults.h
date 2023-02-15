#pragma once

#include <memory>

#include "Spec/Types/SpecResultGroup.h"

namespace Spec::Types {
    class SpecResults {
        std::shared_ptr<SpecResultGroup> _rootResultGroup;
        unsigned int                     _totalTests  = 0;
        unsigned int                     _totalPassed = 0;
        unsigned int                     _totalFailed = 0;

    public:
        SpecResults() : _rootResultGroup(std::make_shared<SpecResultGroup>()) {}

        std::shared_ptr<SpecResultGroup> GetRoot() { return _rootResultGroup; }
        void                             SetRoot(std::shared_ptr<SpecResultGroup> root) { _rootResultGroup = root; }

        unsigned int GetTotalTests() { return _totalTests; }
        void         IncrementTotalTests() { _totalTests++; }

        unsigned int GetTotalPassed() { return _totalPassed; }
        void         IncrementTotalPassed() { _totalPassed++; }

        unsigned int GetTotalFailed() { return _totalFailed; }
        void         IncrementTotalFailed() { _totalFailed++; }
    };
}
