#define spec_file HelloSpecs

#include "SpecHelper.h"  // IWYU pragma: keep

// TODO - Async :)

//////////////
//////////////

TestGroup(TestGroup1) {
    test("some test", []() { AssertThat(1, Equals(1)); });
}

SetupAsync {
    _Log_("HI from async SETUP");
    // assert(1 == 2);
    // throw "Foo!";
    done();
}

TeardownAsync {
    _Log_("HI from async TEARDOWN");
    done();
}

// Tag("Foo", "Bar");  // <--- metadata for specs
// Tags({
//     {"Foo",  "Bar"     },
//     {"Blah", "Whatever"},
// });
TestAsync("Testing something async") {
    _Log_("YOU CALLED the Testing something async TEST!");
    // done();
}

Describe("Some Specs") {
    // FULL list of possible variables for it/setup/teardown
    // it("Something ASYNC", [](SpecsCpp::ISpecComponent* component, SpecsCpp::ISpec* spec,
    //                          SpecsCpp::SpecCodeBlock::SpecCodeBlockAsyncDoneFn* doneFn) {
    //     _Log_("YOU CALLED the Something ASYNC TEST!");
    // });

    // tag("timeout", 30000);
    setup([](SpecDone done) {
        _Log_("HI from async SETUP");
        done();
    });

    teardown([](SpecDone done) {
        _Log_("HI from async TEARDOWN");
        done();
    });

    // tags({
    //     {"foo",  "bar"     },
    //     {"blah", "whatever"},
    // });
    test("Something Async", [](SpecDone done) {
        _Log_("YOU CALLED the Something ASYNC TEST!");
        // throw "KABOOM before done was called";
        // assert(1 == 69);
        AssertThat(1, Equals(69));
        done();
    });
}

Describe("DESCRIBE") {
    setup([]() { _Log_("HI from SETUP"); });
    teardown([]() { _Log_("HI from TEARDOWN"); });
    // it("IT 1", []() { _Log_("HI from IT 1"); });

    describe("CHILD", []() {
        setup([]() {
            _Log_(">> HI from SETUP");
            // throw "BOOM!";
        });
        teardown([]() { _Log_(">> HI from TEARDOWN"); });
        // it("IT 2", []() { _Log_(">> HI from IT 2"); });

        describe("CHILD 2", []() {
            setup([]() { _Log_(">>>> HI from SETUP"); });
            teardown([]() { _Log_(">>>> HI from TEARDOWN"); });
            it("IT 3", []() {
                _Log_("~~>>>> HI from IT 3");
                // AssertThat(1, Equals(69));
            });
        });
    });
}
