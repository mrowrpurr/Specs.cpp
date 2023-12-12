#include "SpecHelper.h"  // IWYU pragma: keep

TestGroup(TestGroup2) {
    test("some MORE test", []() { AssertThat(1, Equals(1)); });
}

Setup { _Log_("HI from SETUP in More More More Specs"); }
