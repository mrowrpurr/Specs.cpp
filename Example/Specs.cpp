#include <Spec/Autorun.h>

using namespace Spec;

Test("This should pass") { Print("Pass!"); }
Test("This should fail") {
    throw "KABOOM!";
    Print("Fail!");
}
Test("This should fail with an exception") {
    throw std::runtime_error("KABOOM exception!");
    Print("Fail!");
}

Describe("some test group") {
    it("prints something", []() { Print("Hello world!"); });
}

Specs {
    describe("group in specs", []() {
        it("prints something in group", []() { Print("Hello world from group test!"); });
    });
}