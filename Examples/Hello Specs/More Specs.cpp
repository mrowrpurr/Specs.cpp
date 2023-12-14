#define spec_file MoreSpecs

#include "SpecHelper.h"  // IWYU pragma: keep

TestGroup("More Specs");

UseTemplate("Cool Template");

Setup { _Log_("More Specs setup"); }

Test("MORE Something") { _Log_("YOU CALLED the Something TEST!"); }

Spec("MORE Something else") {
    _Log_("YOU CALLED the Something else TEST! Gonna throw...");
    // throw "HELLO KABOOM";
}

Spec("MORE This one fails using snowhouse") { AssertThat(1, Is().EqualTo(69)); }
