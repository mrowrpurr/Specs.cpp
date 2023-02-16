#pragma once

#include <any>
#include <unordered_map>

#include "Spec/Types/SpecDiscovery.h"

namespace Spec {

    void describe(const std::string& description, std::function<void(SpecGroup&)> body) {
        Spec::Types::SpecDiscovery::GetGlobalInstance().DiscoverGroup(description, body);
    }

    void describe(const std::string& description, std::function<void()> body) {
        Spec::Types::SpecDiscovery::GetGlobalInstance().DiscoverGroup(description, body);
    }

    void describe(
        const std::string& description, std::unordered_map<std::string, std::any>, std::function<void()> body
    ) {
        Spec::Types::SpecDiscovery::GetGlobalInstance().DiscoverGroup(description, body);
    }
}
