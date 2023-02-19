#pragma once

#include <any>
#include <unordered_map>

#include "Spec/Types/SpecDiscovery.h"

namespace Specs {

    void xit(const std::string& description) {
        Spec::Types::SpecDiscovery::GetGlobalInstance().DiscoverTest(description
        );
    }

    void
    xit(const std::string& description,
        std::function<void(std::function<void()>)>) {
        Spec::Types::SpecDiscovery::GetGlobalInstance().DiscoverTest(description
        );
    }

    void xit(const std::string& description, std::function<void(SpecTest&)>) {
        Spec::Types::SpecDiscovery::GetGlobalInstance().DiscoverTest(description
        );
    }

    void xit(const std::string& description, std::function<void(AsyncSpec&)>) {
        Spec::Types::SpecDiscovery::GetGlobalInstance().DiscoverTest(description
        );
    }

    void xit(const std::string& description, std::function<void()>) {
        Spec::Types::SpecDiscovery::GetGlobalInstance().DiscoverTest(description
        );
    }

    void
    xit(const std::string& description,
        std::unordered_map<std::string, std::any>, std::function<void()>) {
        Spec::Types::SpecDiscovery::GetGlobalInstance().DiscoverTest(description
        );
    }
}
