// #include "SpecHelper.h"

// This is going to build and run tests
// using STRUCTS ONLY - NO DSL

#include <Spec/SpecGroup.h>
#include <Spec/SpecRunner.h>
#include <Spec/SpecTest.h>

#include <format>
#include <iostream>

using namespace Spec;

void Log(const std::string& text) { std::cout << text << std::endl; }

void SetupAndRunSpecs() {
    // Every spec needs a group!
    SpecGroup group{.description = "This is the group!"};

    // Let's create a spec!
    SpecTest test{.description = "This is a test!"};
    test.body = [](SpecTest& test) {
        Log(std::format("Holy shit, the body of this test ran. Test: {}", test.description));
        test.promise.set_value(true);
    };

    group.tests.emplace_back(std::move(test));

    // Run the group!
    SpecRunner runner;
    runner.RunGroup(group);
}

int main() { SetupAndRunSpecs(); }
