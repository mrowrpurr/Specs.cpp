#define SPEC_GROUP Main_Entrypoint

#include <Specs/SpecApplication.h>

#include "SpecHelper.h"  // IWYU pragma: keep

Example("running code main() entrypoint with no registered options") {
    TestSpecOutput  standardOutput;
    TestSpecOutput  standardError;
    SpecApplication app;

    app.environment()->set_standard_output(&standardOutput);
    app.environment()->set_error_output(&standardError);

    app.main();
}

// StartTestGroup("with zero configuration") {
//     Example("First example") {}
// }
// EndTestGroup();
