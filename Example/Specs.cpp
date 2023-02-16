#include <Spec/Autorun.h>

using namespace Spec;

Test("Cool shit") {}

Test("This should pass") {}

Test("This should fail") {
    throw "KABOOM!";
    Print("Fail!");
}

Test("This should fail with an exception") { throw std::runtime_error("KABOOM exception!"); }

Describe("some test group") {
    it("prints something", []() {});
}

Specs {
    describe("group in specs", []() { it("prints something in group", []() {}); });
}