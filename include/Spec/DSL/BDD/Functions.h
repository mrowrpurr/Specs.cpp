#pragma once

#include "Spec/SpecContext.h"

namespace Spec {

    void describe(const std::string& description, std::function<void(SpecGroup&)> body) {
        SpecContext::GetDefault().GetDiscovery().DiscoverGroup(description, body);
    }

    void describe(const std::string& description, std::function<void()> body) {
        SpecContext::GetDefault().GetDiscovery().DiscoverGroup(description, body);
    }

    void it(const std::string& description, std::function<void(SpecTest&)> body) {
        SpecContext::GetDefault().GetDiscovery().DiscoverTest(description, body);
    }

    void it(const std::string& description, std::function<void()> body) {
        SpecContext::GetDefault().GetDiscovery().DiscoverTest(description, body);
    }

    void test(const std::string& description, std::function<void(SpecTest&)> body) {
        SpecContext::GetDefault().GetDiscovery().DiscoverTest(description, body);
    }

    void test(const std::string& description, std::function<void()> body) {
        SpecContext::GetDefault().GetDiscovery().DiscoverTest(description, body);
    }
}
