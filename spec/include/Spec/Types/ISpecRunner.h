#pragma once

#include "Spec/Types/ISpecExceptionHandler.h"
#include "Spec/Types/ISpecReporter.h"
#include "Spec/Types/SpecRegistry.h"
#include "Spec/Types/SpecResults.h"

namespace Spec::Types {
    class ISpecRunner {
    public:
        virtual void RunSpecs(
            std::shared_ptr<std::promise<bool>> complete, SpecRegistry& registry, SpecResults& results,
            std::vector<std::shared_ptr<ISpecReporter>>         reporters,
            std::vector<std::shared_ptr<ISpecExceptionHandler>> exceptionHandlers
        ) = 0;
    };
}
