#pragma once

#include "Spec/SpecDiscovery.h"
#include "Spec/SpecRegistry.h"

namespace Spec {

    //! Represents a context containing groups of specs
    /**
     * Connects SpecDiscovery with SpecRegistry
     */
    class SpecContext {
        SpecDiscovery _discovery;
        SpecRegistry  _registry;

    public:
        SpecContext() : _discovery(_registry) {}

        /** Global, default SpecContext */
        static SpecContext& GetDefault() {
            static SpecContext context;
            return context;
        }

        SpecDiscovery& GetDiscovery() { return _discovery; }
        SpecRegistry&  GetRegistry() { return _registry; }
    };
}
