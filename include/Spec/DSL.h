#pragma once

#include "Spec/Internal/DefineSpecGroup.h"
#include "Spec/Internal/DefineSpecTest.h"
#include "Spec/Internal/Macros/Describe.h"
#include "Spec/Internal/Macros/RunSpecsMain.h"
#include "Spec/Internal/Macros/Specs.h"
#include "Spec/Internal/Macros/Test.h"
#include "Spec/Internal/SpecController.h"

namespace Spec {

    void describe(const std::string& description, std::function<void(SpecGroup&)> body) {
        Internal::_DefineSpecGroup_(description, body);
    }

    void describe(const std::string& description, std::function<void()> body) {
        Internal::_DefineSpecGroup_(description, [body](auto&) { body(); });
    }

    void it(const std::string& description, std::function<void(SpecTest&)> body) {
        Internal::_DefineSpecTest_(description, body);
    }

    void it(const std::string& description, std::function<void()> body) {
        Internal::_DefineSpecTest_(description, [body](auto&) { body(); });
    }

    void test(const std::string& description, std::function<void(SpecTest&)> body) {
        Internal::_DefineSpecTest_(description, body);
    }

    void test(const std::string& description, std::function<void()> body) {
        Internal::_DefineSpecTest_(description, [body](auto&) { body(); });
    }
}
