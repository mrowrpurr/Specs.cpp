#pragma once

#include "Spec/SpecGroup.h"
#include "Spec/Types/ISpecExceptionHandler.h"
#include "Spec/Types/ISpecReporter.h"
#include "Spec/Types/SpecResults.h"

namespace Spec::Types {
    class ISpecRunner {
    public:
        virtual void RunSpecs(
            std::shared_ptr<std::promise<bool>> complete, std::shared_ptr<SpecGroup>, SpecResults& results,
            std::vector<std::shared_ptr<ISpecReporter>>         reporters,
            std::vector<std::shared_ptr<ISpecExceptionHandler>> exceptionHandlers
        ) = 0;
    };
}
