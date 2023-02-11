#pragma once

#include <format>
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

        std::vector<std::function<void()>> _unevaluatedSpecsBlocks;
        Internal::EventLoop                _eventLoop;

    public:
        // just to hack things together quickly for testing things...
        std::promise<bool> _currentlyRunningTestResultPromise;
        std::atomic<bool>  _currentlyRunningTestPassed;

        static SpecController& GetSingleton() {
            static SpecController singleton;
            return singleton;
        }

        void _RegisterSpecBlockToEvaluate(std::function<void()> fn) {
            _unevaluatedSpecsBlocks.emplace_back(fn);
        }

        void RunSpecs() {
            for (auto& block : _unevaluatedSpecsBlocks) block();
        }

        void RunSpec(const std::string& description, std::function<void()> body) {
            _eventLoop.enqueue([body, description]() {
                try {
                    body();
                    GetSingleton()._currentlyRunningTestPassed = true;
                    std::cout << std::format("sync TEST PASSED!: '{}'", description) << std::endl;
                } catch (...) {
                    GetSingleton()._currentlyRunningTestPassed = false;
                    std::cout << std::format("sync TEST FAILED!: '{}'", description) << std::endl;
                }
            });
        }

        // TODO: time
        void RunSpecAsync(
            const std::string& description, std::function<void(std::promise<bool>&)> body
        ) {
            _currentlyRunningTestResultPromise = {};
            _eventLoop.enqueue([&]() {
                try {
                    body(GetSingleton()._currentlyRunningTestResultPromise);
                } catch (...) {
                    std::cout << std::format(
                                     "*async* TEST FAILED! with unexpected error: '{}'", description
                                 )
                              << std::endl;
                    _currentlyRunningTestResultPromise.set_value(false);
                }
            });
            auto future = _currentlyRunningTestResultPromise.get_future();
            auto result = future.get();
            std::cout << std::format(
                             "Ran *ASYNC* test {} and the result was {}", description, result
                         )
                      << std::endl;
        }
    };
}
