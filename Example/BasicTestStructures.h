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

    // Test 1
    group.tests.emplace_back(SpecTest{
        .description = "Test1 desc", .body = [](auto&) { Log("Hello from Test 1"); }});

    // Test 2
    group.tests.emplace_back(SpecTest{
        .description = "Test2 desc", .body = [](auto&) { Log("Hello from Test 2"); }});

    // Setup1
    group.setups.emplace_back(SpecTest{.body = [](auto&) { Log("Hello from Setup 1"); }});

    // Setup2
    group.setups.emplace_back(SpecTest{.body = [](auto&) { Log("Hello from Setup 2"); }});

    // Teardown1
    group.teardowns.emplace_back(SpecTest{.body = [](auto&) { Log("Hello from Teardown 1"); }});

    // Teardown2
    group.teardowns.emplace_back(SpecTest{.body = [](auto&) { Log("Hello from Teardown 2"); }});

    // Run the group!
    SpecRunner runner;
    runner.RunGroup(group);
}

int main() { SetupAndRunSpecs(); }
