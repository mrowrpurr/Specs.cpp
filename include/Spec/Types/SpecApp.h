#pragma once

#include <memory>

#include "Spec/Types/ISpecReporter.h"
#include "Spec/Types/ISpecRunner.h"
#include "Spec/Types/SpecDefinitionBlocks.h"
#include "Spec/Types/SpecDiscovery.h"
#include "Spec/Types/SpecRegistry.h"
#include "Spec/Types/SpecResults.h"

namespace Spec::Types {

    class SpecApp {
        static std::shared_ptr<SpecApp> _defaultInstance;

    public:
        SpecRegistry  Registry;
        SpecDiscovery Discovery;
        SpecResults   Results;

        std::shared_ptr<ISpecRunner>                Runner;
        std::vector<std::shared_ptr<ISpecReporter>> Reporters;

        static std::shared_ptr<SpecApp> GetDefaultInstance() {
            if (!_defaultInstance) {
                _defaultInstance = std::make_shared<SpecApp>();
                _defaultInstance->Discovery.SetRegistry(_defaultInstance->Registry);
            }
            return _defaultInstance;
        }

        void LoadDefinitionBlocks() {
            auto& globalSpecDiscovery = SpecDiscovery::GetGlobalInstance();
            SpecDiscovery::SetGlobalInstance(Discovery);
            SpecDefinitionBlocks::GetGlobalInstance().EvaluateBlocks();
            SpecDiscovery::SetGlobalInstance(globalSpecDiscovery);
        }

        void Run() {}
    };

    std::shared_ptr<SpecApp> SpecApp::_defaultInstance;
}