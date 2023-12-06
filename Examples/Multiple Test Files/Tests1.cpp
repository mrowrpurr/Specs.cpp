#define spec_name Test1

#include <Specs/SpecHelper.h>

Describe("1ONE1 A group of tests") {
    it("1ONE1 should pass", []() { AssertThat(1, Is().EqualTo(1)); });
    it("1ONE1 should fail", []() { AssertThat(1, Is().EqualTo(111)); });
}
