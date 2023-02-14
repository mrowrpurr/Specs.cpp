#pragma once

#include "Spec/SpecRunner.h"

namespace Spec::Runners {

    // TODO - get MVP working!
    class EventLoopRunner : public SpecRunner {
    public:
        void RunSpecs(std::promise<void>&, SpecSession&, std::shared_ptr<SpecReporter>) override {
            // Let's as LAZILY as possible... RUN THE TESTS!
        }
    };
}
