#include <Spec/Autorun.h>

//////////////////////
// TODO
// - catch thrown exception (...) and std::exception with .what()
// - setup/teardown
// - get promise
// - get callback, void or bool
// - provide tags
// - setup/teardown/tests have access to testdata<> (powered by map<str,any>)
//////////////////////

using namespace Spec;

Test("top-level test") { Print("Hi from top-level test!"); }

Describe("top-level-describe") {
    it("inside top-level describe", []() { Print("this is inside top level describe"); });
}

Specs {
    test("something", []() {});

    test(
        "description",
        {
            {   "tags", "foo,bar"},
            {"another",    "blah"}
    },
        []() {}
    );

    test("description", tags({"foo", "bar"}), []() { auto tags = "making sure this works"; });

    describe("Dog", []() {
        it("barks", []() { Print("THIS IS THE BODY OF THE DOG TEST"); });
        describe("Certain type of dog", []() {
            it("Does certain thing", []() { Print("THIS IS THE BODY OF THE CAT TEST"); });
        });
    });
}

// Test("fail just a string") { throw "just a string!"; }
// Test("fail std::exception") { throw std::runtime_error("Boom! Runtime error!"); }
