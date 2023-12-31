#define SPEC_GROUP Main_Entrypoint

#include <Specs/SpecApplication.h>

#include "SpecHelper.h"  // IWYU pragma: keep

Example("running code main() entrypoint with no registered options") {
    auto app = unique_ptr<ISpecApplication>(new SpecApplication());
    app->main();
}

// StartTestGroup("with zero configuration") {
//     Example("First example") {}
// }
// EndTestGroup();
