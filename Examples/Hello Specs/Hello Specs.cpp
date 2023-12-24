#define SPEC_GROUP Hello_Specs

#include "SpecHelper.h"  // IWYU pragma: keep

TestAsync("Async Test") {
    _Log_("Hello from Async Test");
    done();
}

// Tag("tag1");
Teardown { _Log_("Hello from Teardown"); }

// MetaData("key", "value");
GroupSetup {
    // current_spec
    _Log_("Hello from GroupSetup");
}

// MetaDatas({"key1", "value1"}, {"key2", "value2"});
GroupTeardown { _Log_("Hello from GroupTeardown"); }

Tag("tag1");
Tags("tag2", "tag3");
Test("Test One") {
    _Log_("Hello from Test One");
    auto foreach = unique_function_pointer([](const char* tag) { _Log_("Tag: {}", tag); });
    current_spec->tags()->foreach(foreach.get());
}

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

DescribeFn(This_is_my_describe) {
    test("some test", []() { _Log_("Hi from test!"); });
}