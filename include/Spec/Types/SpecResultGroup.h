#pragma once

#include <string>
#include <vector>

#include "Spec/Types/SpecResultTest.h"

namespace Spec::Types {
    class SpecResultGroup {
        unsigned int                 _totalTests  = 0;
        unsigned int                 _totalPassed = 0;
        unsigned int                 _totalFailed = 0;
        std::vector<SpecResultGroup> _groups;
        std::vector<SpecResultTest>  _tests;

    public:
        std::string description;

        unsigned int GetTotalTests() { return _totalTests; }
        void         IncrementTotalTests() { _totalTests++; }

        unsigned int GetTotalPassed() { return _totalPassed; }
        void         IncrementTotalPassed() { _totalPassed++; }

        unsigned int GetTotalFailed() { return _totalFailed; }
        void         IncrementTotalFailed() { _totalFailed++; }

        std::vector<SpecResultGroup>& GetGroups() { return _groups; }
        std::vector<SpecResultTest>&  GetTests() { return _tests; }

        void AddGroup(SpecResultGroup& group) { _groups.push_back(group); }
        void AddTest(SpecResultTest& test) { _tests.push_back(test); }
    };
}
