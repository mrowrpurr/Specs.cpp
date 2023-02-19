#pragma once

#include <any>
#include <unordered_map>

#include "Spec/Types/SpecDiscovery.h"

namespace Specs {

    // TODO: xtest() for all variations of test()

    void test(const std::string& description) {
        Spec::Types::SpecDiscovery::GetGlobalInstance().DiscoverTest(description
        );
    }

    void test(
        const std::string& description, std::function<void(SpecTest&)> body
    ) {
        Spec::Types::SpecDiscovery::GetGlobalInstance().DiscoverTest(
            description, body
        );
    }

    void test(const std::string& description, std::function<void()> body) {
        Spec::Types::SpecDiscovery::GetGlobalInstance().DiscoverTest(
            description, body
        );
    }

    void test(
        const std::string& description,
        std::unordered_map<std::string, std::any>, std::function<void()> body
    ) {
        Spec::Types::SpecDiscovery::GetGlobalInstance().DiscoverTest(
            description, body
        );
    }
}
