#include "SpecHelper.h"

TestGroup("Setup and Teardown");

TODO("Top-level setup and teardown");

Describe("Within a top-level describe") { todo("Setup and teardown"); }

Specs {
    describe("hello!", []() {
        std::string hello = "hello";

        setup([]() {
            Print("runnnn! THIS IS SETUP!");
            // Print("In setup, hello is: " + hello);
            // hello = "hello updated by setup";
        });

        teardown([&]() {
            Print("runnnn! THIS IS TEARDONW!");
            // Print("In teardown, hello is: " + hello);
        });

        it("a test!", [hello]() { AssertThat(hello, Equals("hello updated by setup")); });
    });
}
