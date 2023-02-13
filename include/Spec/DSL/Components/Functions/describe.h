#pragma once

#include <any>
#include <unordered_map>

#include "Spec/SpecContext.h"

namespace Spec {

    void describe(const std::string& description, std::function<void(SpecGroup&)> body) {
        SpecContext::GetDefault().GetDiscovery().DiscoverGroup(description, body);
    }

    void describe(const std::string& description, std::function<void()> body) {
        SpecContext::GetDefault().GetDiscovery().DiscoverGroup(description, body);
    }

    void describe(
        const std::string& description, std::unordered_map<std::string, std::any>, std::function<void()> body
    ) {
        SpecContext::GetDefault().GetDiscovery().DiscoverGroup(description, body);
    }
}
