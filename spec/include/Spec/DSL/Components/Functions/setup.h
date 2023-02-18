#pragma once

#include <any>
#include <unordered_map>

#include "Spec/Types/SpecDiscovery.h"

namespace Spec {

    // TODO - other overloads

    void setup(std::function<void(SpecTest&)> body) {
        Spec::Types::SpecDiscovery::GetGlobalInstance().DiscoverSetup(body);
    }

    void setup(std::function<void()> body) { Spec::Types::SpecDiscovery::GetGlobalInstance().DiscoverSetup(body); }
}
