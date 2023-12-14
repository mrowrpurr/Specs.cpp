#include "SpecHelper.h"  // IWYU pragma: keep

DescribeFn(WithoutSpecFileTwo) {
    test("test", [] { _Log_("Hi from test in " __FILE__ ""); });
}
