#define spec_name Test2

#include <Specs/SpecHelper.h>

Describe("2two2 A group of tests") {
    it("2two2 should pass", []() { AssertThat(1, Is().EqualTo(1)); });
    it("2two2 should fail", []() { AssertThat(1, Is().EqualTo(222)); });
}
