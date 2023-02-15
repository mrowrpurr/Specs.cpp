#pragma once

#include "Spec/Types/ISpecReporter.h"
#include "Spec/Types/SpecRegistry.h"
#include "Spec/Types/SpecResults.h"

namespace Spec::Types {
    class ISpecRunner {
    public:
        virtual void RunSpecs(
            std::promise<void>& complete, SpecRegistry& registry, SpecResults& results,
            std::vector<ISpecReporter> reporters
        ) = 0;
    };
}
