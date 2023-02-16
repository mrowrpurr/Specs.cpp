#pragma once

#include <memory>

#include "Spec/Types/ExceptionHandlers/DefaultExceptionHandler.h"
#include "Spec/Types/ISpecExceptionHandler.h"
#include "Spec/Types/ISpecReporter.h"
#include "Spec/Types/ISpecRunner.h"
#include "Spec/Types/SpecDefinitionBlocks.h"
#include "Spec/Types/SpecDiscovery.h"
#include "Spec/Types/SpecExtensionsRegistry.h"
#include "Spec/Types/SpecRegistry.h"
#include "Spec/Types/SpecResults.h"

namespace Spec::Types {

    class SpecApp {
        static std::shared_ptr<SpecApp> _defaultInstance;

    public:
        SpecRegistry  Registry;
        SpecDiscovery Discovery;
        SpecResults   Results;

        std::shared_ptr<ISpecRunner>                        Runner;
        std::vector<std::shared_ptr<ISpecReporter>>         Reporters;
        std::vector<std::shared_ptr<ISpecExceptionHandler>> ExceptionHandlers;

        static std::shared_ptr<SpecApp> GetDefaultInstance() {
            if (!_defaultInstance) {
                Print("SETUP DEFAULT INSTANCE");
                _defaultInstance = std::make_shared<SpecApp>();
                _defaultInstance->Discovery.SetRegistry(_defaultInstance->Registry);
                _defaultInstance->ExceptionHandlers.emplace_back(
                    std::make_shared<Spec::Types::ExceptionHandlers::DefaultExceptionHandler>()
                );
                auto& specExtensionRegistry = SpecExtensionsRegistry::GetRegistry();
                for (auto& handler : specExtensionRegistry.GetExceptionHandlers())
                    _defaultInstance->ExceptionHandlers.insert(_defaultInstance->ExceptionHandlers.begin(), handler);
                Print("This app has {} exception handlers", _defaultInstance->ExceptionHandlers.size());
            }
            return _defaultInstance;
        }

        void LoadDefinitionBlocks() {
            auto& globalSpecDiscovery = SpecDiscovery::GetGlobalInstance();
            SpecDiscovery::SetGlobalInstance(Discovery);
            SpecDefinitionBlocks::GetGlobalInstance().EvaluateBlocks();
            SpecDiscovery::SetGlobalInstance(globalSpecDiscovery);
        }

        std::shared_ptr<std::promise<bool>> Run() {
            auto promise = std::make_shared<std::promise<bool>>();
            if (!Runner) {
                promise->set_value(false);
                return promise;
            }
            Runner->RunSpecs(promise, Registry, Results, Reporters, ExceptionHandlers);
            return promise;
        }

        int RunAndWait(std::chrono::duration<long long> timeout = std::chrono::seconds(0)) {
            auto promise = Run();
            auto future  = promise->get_future();
            if (timeout.count() > 0) {
                if (future.wait_for(timeout) == std::future_status::timeout) {
                    return 2;
                }
            }
            return future.get() ? 0 : 1;
        }
    };

    std::shared_ptr<SpecApp> SpecApp::_defaultInstance;
}