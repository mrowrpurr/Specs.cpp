#pragma once

#include <any>
#include <string>
#include <unordered_map>
#include <vector>

namespace Spec {

    std::unordered_map<std::string, std::any> tags(std::vector<std::string> tags) {
        return {
            {"tags", tags}
        };
    }

}
