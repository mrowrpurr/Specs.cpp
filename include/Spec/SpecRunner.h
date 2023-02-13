#pragma once

#include <future>

#include "Spec/SpecReporter.h"
#include "Spec/SpecSession.h"

namespace Spec {

    class SpecRunner {
    public:
        virtual void RunSpecs(std::promise<void>&, SpecSession&, SpecReporter&) {
            throw "Not implemented";
        }
    };
}