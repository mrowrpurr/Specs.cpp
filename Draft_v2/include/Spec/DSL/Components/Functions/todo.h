#pragma once

#include <any>
#include <unordered_map>

#include "Spec/Types/SpecDiscovery.h"

namespace Specs {

    void todo(const std::string& description) {
        Spec::Types::SpecDiscovery::GetGlobalInstance().DiscoverTest(description
        );
    }
}
