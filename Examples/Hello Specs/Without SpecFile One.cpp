#include "SpecHelper.h"  // IWYU pragma: keep

DescribeFn(WithoutSpecFileOne) {
    test("test", [] { _Log_("Hi from test in " __FILE__ ""); });
}
