#define spec_file MoreSpecs

#include "SpecHelper.h"  // IWYU pragma: keep

TestGroup("More Specs");

Config { _Log_("Hi from config"); }
Config { _Log_("Hi from another config"); }
Configure { _Log_("Hi from configure"); }

Setup {
    if (!current_group->has_var("number")) current_group->var("number", 42);
}

SetupAsync { done(); }

Describe("Child Group") {
    test("Child Test", [](SpecsCpp::ISpecGroup* group) {
        AssertThat(group->var<int>("number"), Equals(42));
    });
}

EndTestGroup();
