#pragma once

#include <functional>
#include <iostream>
#include <queue>

#include "Spec/Internal/EventLoop.h"
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

        std::queue<std::function<void()>> _unevaluatedSpecsBlocks;
        Internal::EventLoop               _eventLoop;

    public:
        static SpecController& GetSingleton() {
            static SpecController singleton;
            return singleton;
        }

        void _RegisterSpecBlockToEvaluate(std::function<void()> fn) {
            _unevaluatedSpecsBlocks.push(fn);
        }

        void RunSpecs() {
            std::cout << "RunSpecs()" << std::endl;
            std::cout << "Run some stuff in the event loop!" << std::endl;
            _eventLoop.enqueue([]() { std::cout << "RUN ME" << std::endl; });
            _eventLoop.enqueue([]() { std::cout << "RUN TOO" << std::endl; });
        }
    };
}
