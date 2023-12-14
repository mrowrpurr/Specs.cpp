#define spec_file MoreMoreSpecs

#include "SpecHelper.h"  // IWYU pragma: keep

// SetTestGroup("More More More Specs");
UnsetTestGroup();

Setup { _Log_("3x More More More Specs"); }

TestGroupFn(TestGroup2) {
    test("some MORE test", []() { AssertThat(1, Equals(1)); });
}
