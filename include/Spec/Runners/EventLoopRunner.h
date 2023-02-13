#pragma once

#include "Spec/SpecRunner.h"

namespace Spec::Runners {

    // TODO - get MVP working!
    class EventLoopRunner : public SpecRunner {
    public:
        void RunSpecs(std::promise<void>&, SpecSession&, SpecReporter&) override {
            Print("Run Specs with event loop!");
        }
    };
}
