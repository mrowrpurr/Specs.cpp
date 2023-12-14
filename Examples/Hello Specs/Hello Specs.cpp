#define spec_name HelloSpecs

#include "SpecHelper.h"  // IWYU pragma: keep

Config { _Log_("Hi from config"); }
Config { _Log_("Hi from another config"); }
Configure { _Log_("Hi from configure"); }

class Dog {
public:
    Dog() { _Log_("Hi from Dog constructor"); }
    ~Dog() { _Log_("Hi from Dog destructor"); }
};

Setup {
    if (!current_group->has_var("number")) current_group->var("number", 42);
    current_spec->var("dog", new Dog(), false);
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
