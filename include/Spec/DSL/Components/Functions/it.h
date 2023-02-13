#pragma once

#include <any>
#include <unordered_map>

#include "Spec/SpecContext.h"

namespace Spec {

    void it(const std::string& description, std::function<void(SpecTest&)> body) {
        SpecContext::GetDefault().GetDiscovery().DiscoverTest(description, body);
    }

    void it(const std::string& description, std::function<void()> body) {
        SpecContext::GetDefault().GetDiscovery().DiscoverTest(description, body);
    }

    void it(const std::string& description, std::unordered_map<std::string, std::any>, std::function<void()> body) {
        SpecContext::GetDefault().GetDiscovery().DiscoverTest(description, body);
    }
}
