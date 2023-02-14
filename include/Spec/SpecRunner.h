#pragma once

#include <future>

#include "Spec/SpecSession.h"

namespace Spec {

    class SpecRunner {
    public:
        // TODO - make real abstract
        virtual void RunSpecs(std::promise<void>&, SpecSession&) { throw "Not implemented"; }
    };
}