#define spec_file HelloSpecs

#include "SpecHelper.h"  // IWYU pragma: keep

TestGroup("Root Specs Group");

Setup {
    if (!current_group->has_var("number")) current_group->var("number", 42);
}

SetupAsync { done(); }

Describe("Hello Specs") {
    test("Hello Specs", [](SpecsCpp::ISpecGroup* group) {
        AssertThat(group->var<int>("number"), Equals(42));
    });
}
