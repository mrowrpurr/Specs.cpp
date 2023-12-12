#define spec_file MoreMoreSpecs

#include "SpecHelper.h"  // IWYU pragma: keep

// SetTestGroup("More More More Specs");

Setup { _Log_("3x More More More Specs"); }

TestGroup(TestGroup2) {
    test("some MORE test", []() { AssertThat(1, Equals(1)); });
}
