#pragma once

#include <functional>
#include <iostream>
#include <queue>

#include "Spec/SpecGroup.h"

namespace Spec {

    //! Store defined specs and their results!
    class SpecController {
        SpecController()                                 = default;
        ~SpecController()                                = default;
        SpecController(const SpecController&)            = delete;
        SpecController(SpecController&&)                 = delete;
        SpecController& operator=(const SpecController&) = delete;
        SpecController& operator=(SpecController&&)      = delete;

        std::queue<std::function<void()>> _unevaluatedSpecDSLMacros;

    public:
        static SpecController& GetSingleton() {
            static SpecController singleton;
            return singleton;
        }

        void _RegisterSpecBlockToEvaluate(std::function<void()> fn) {
            std::cout << "REGISTERED A SPEC MACRO BLOCK!!" << std::endl;
            std::cout << "... let's run it ..." << std::endl;
            _unevaluatedSpecDSLMacros.push(fn);
            fn();
        }
    };
}
