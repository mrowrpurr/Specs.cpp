#pragma once

#include <functional>
#include <string>

#include "Spec/Internal/SpecController.h"
#include "Spec/SpecTest.h"

namespace Spec::Internal {
    void _DefineSpecTest_(const std::string& description, std::function<void(SpecTest&)> body) {
        SpecController::GetSingleton().DefineSpecTest(description, body);
    }
}