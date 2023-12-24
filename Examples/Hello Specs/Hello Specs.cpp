#include "SpecHelper.h"  // IWYU pragma: keep

Test("Foo") {}

Describe("Describe 1") {
    test("test 1", []() { _Log_("test 1"); });

    skip();
    test("test 2", []() { _Log_("test 2"); });
}
