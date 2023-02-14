#pragma once

#include <future>

#include "Spec/SpecSession.h"

namespace Spec {

    class SpecRunner {
    public:
        virtual void RunSpecs(std::promise<void>&, SpecSession&) { throw "Not implemented"; }
    };
}