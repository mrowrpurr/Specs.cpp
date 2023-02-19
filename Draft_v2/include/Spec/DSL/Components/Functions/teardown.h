#pragma once

#include <any>
#include <unordered_map>

#include "Spec/Types/SpecDiscovery.h"

namespace Specs {

    // TODO - other overloads

    void teardown(std::function<void(SpecTest&)> body) {
        Spec::Types::SpecDiscovery::GetGlobalInstance().DiscoverTeardown(body);
    }

    void teardown(std::function<void()> body) {
        Spec::Types::SpecDiscovery::GetGlobalInstance().DiscoverTeardown(body);
    }
}
