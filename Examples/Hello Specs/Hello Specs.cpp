#define spec_name HelloSpecs

#include "SpecHelper.h"  // IWYU pragma: keep

TestAsync("Async Test") {
    _Log_("Hello from Async Test");
    done();
}

Teardown { _Log_("Hello from Teardown"); }

GroupSetup { _Log_("Hello from GroupSetup"); }

GroupTeardown { _Log_("Hello from GroupTeardown"); }

Test("Test One") { _Log_("Hello from Test One"); }

Test("Test Two") { _Log_("Hello from Test Two"); }

Test("Test Three") { _Log_("Hello from Test Three"); }

TestGroup("Group 2");

Test("Test Four") { _Log_("Hello from Test Four"); }

Describe("Describe 1") {
    //
    test("something", [current_group]() {
        _Log_("Hi from test, the current group is: {}", current_group->description());
    });
}
