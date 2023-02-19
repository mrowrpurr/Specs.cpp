#include "SpecHelper.h"

TestGroup("Setup and Teardown");

namespace {
    std::string setupText;
    std::string teardownText;
    std::string mixedText;
    std::string nestedText;
}

Describe("Setup runs before each test") {
    setup([&]() { setupText += "setup "; });
    it("test 1", [&]() { AssertThat(setupText, Equals("setup ")); });
    it("test 2", [&]() { AssertThat(setupText, Equals("setup setup ")); });
}

Describe("Teardown runs after each test") {
    teardown([&]() { teardownText += "teardown "; });
    it("test 1", [&]() { AssertThat(teardownText, Equals("")); });
    it("test 2", [&]() { AssertThat(teardownText, Equals("teardown ")); });
}

Describe("Setup and Teardown can be mixed") {
    setup([&]() { mixedText += "setup "; });
    teardown([&]() { mixedText += "teardown "; });
    it("test 1", [&]() { AssertThat(mixedText, Equals("setup ")); });
    it("test 2", [&]() { AssertThat(mixedText, Equals("setup teardown setup ")); });
}

Describe("Setup and Teardown can be nested") {
    setup([&]() { nestedText += "setup "; });
    teardown([&]() { nestedText += "teardown "; });
    it("test 1", [&]() { AssertThat(nestedText, Equals("setup ")); });
    it("test 2", [&]() { AssertThat(nestedText, Equals("setup teardown setup ")); });
    describe("nested describe", [&]() {
        setup([&]() { nestedText += "innerSetup "; });
        teardown([&]() { nestedText += "innerTeardown "; });
        it("test 3", [&]() { AssertThat(nestedText, Equals("setup teardown setup teardown innerSetup ")); });
        it("test 4", [&]() {
            AssertThat(nestedText, Equals("setup teardown setup teardown innerSetup innerTeardown innerSetup "));
        });
    });
}
