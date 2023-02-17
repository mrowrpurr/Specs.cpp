#include "SpecHelper.h"

TestGroup("Setup and Teardown");

TODO("A test that I should write!");

xTest("Something") {
    //
    Print("xTest RAN!");
}

Describe("All the tests in here will be skipped") {
    it("should this show up at all?");
    todo("This one is todo");
    pending("This one is pending");
}
