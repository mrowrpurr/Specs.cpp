#define SPEC_GROUP Hello_Hello

#include "SpecHelper.h"  // IWYU pragma: keep

Skip Setup { _Log_("Setup"); }

Test("Foo") {
    //
}

SetTimeoutMs(1000);
Test("Bar") {
    //
}
