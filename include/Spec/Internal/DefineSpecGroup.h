#pragma once

#include <functional>
#include <string>

#include "Spec/Internal/SpecController.h"

namespace Spec::Internal {
    void _DefineSpecGroup_(const std::string& description, std::function<void()> body) {
        SpecController::GetSingleton().DefineSpecGroup(description, body);
    }
}
