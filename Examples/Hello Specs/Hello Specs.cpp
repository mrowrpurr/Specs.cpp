#define SPEC_GROUP Hello_Specs

#include "SpecHelper.h"  // IWYU pragma: keep

TestAsync("Async Test") {
    _Log_("Hello from Async Test");
    done();
}

Teardown { _Log_("Hello from Teardown"); }

GroupSetup {
    // current_spec
    _Log_("Hello from GroupSetup");
}

GroupTeardown { _Log_("Hello from GroupTeardown"); }

Tag("tag1");
Tags("tag2", "tag3");
MetaData("key1", "string value");
MetaData("key2", 123);
MetaData("key3", 123.456);
// Skip();
Test("Test One THIS TEST HERE!!!!!!!!") {
    _Log_("Hello from Test One");
    current_spec->tags()->foreach([](const char* tag) { _Log_("xxx Tag: {}", tag); });
    current_spec->data()->foreach([](SpecsCpp::ISpecDataValue* value) {
        _Log_("xxx Meta Key: {}, Value: {}", value->key(), value->to_string());
    });
}

// SetTimeout(5000);
// TestAsync("I do not finish...") {
//     //
// }

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