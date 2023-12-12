#include "SpecHelper.h"  // IWYU pragma: keep

SetTestGroup("More More Specs");

Describe("Some Group") {
    test("some test", []() { AssertThat(1, Equals(1)); });
}