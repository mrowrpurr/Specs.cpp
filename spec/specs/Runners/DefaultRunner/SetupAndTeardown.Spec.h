#include "SpecHelper.h"

TestGroup("Setup and Teardown");

// TODO("Top-level setup and teardown");

// Describe("Within a top-level describe") { todo("Setup and teardown"); }

Specs {
    describe("hello!", []() {
        std::string hello = "hello";

        setup([]() {
            //
        });

        teardown([&]() {
            //
        });

        it("a test!", [hello]() {
            //
        });
    });
}
