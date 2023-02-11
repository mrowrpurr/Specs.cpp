#pragma once

#include <format>
#include <iostream>
#include <string>
#include <vector>

#include "Spec/SpecGroup.h"
#include "Spec/SpecTest.h"

namespace Spec::Internal {

    //! Singleton where SpecGroup and unevaluated blocks are stored
    /**
     * Used for:
     * - ...
     */
    class SpecStorage {
        SpecStorage()                              = default;
        ~SpecStorage()                             = default;
        SpecStorage(const SpecStorage&)            = delete;
        SpecStorage(SpecStorage&&)                 = delete;
        SpecStorage& operator=(const SpecStorage&) = delete;
        SpecStorage& operator=(SpecStorage&&)      = delete;

        std::vector<std::string> _somethings;

    public:
        static SpecStorage& GetSingleton() {
            static SpecStorage singleton;
            return singleton;
        }

        void AddSomething(const std::string& something) { _somethings.emplace_back(something); }

        std::vector<std::string>& GetSomethings() { return _somethings; }
    };
}
