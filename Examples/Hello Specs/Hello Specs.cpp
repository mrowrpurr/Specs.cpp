#define spec_file HelloSpecs

#include "SpecHelper.h"  // IWYU pragma: keep

BeginTestGroup("Hello Specs");

Config { _Log_("Hi from config"); }
Config { _Log_("Hi from another config"); }
Configure { _Log_("Hi from configure"); }

Setup {
    if (!current_group->has_var("number")) current_group->var("number", 42);
}
SetupAsync { done(); }

Teardown { _Log_("Hi from teardown"); }
TeardownAsync { done(); }

Describe("Child Group") {
    test("Child Test", [](SpecsCpp::ISpecGroup* group) {
        AssertThat(group->var<int>("number"), Equals(42));
    });
}

DescribeFn(SomeSymbolHere) {
    it("should be able to use a function as a test", []() { AssertThat(true, Equals(true)); });
}

EndTestGroup();
