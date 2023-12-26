#pragma once

#include <Specs/SpecDone.h>

#include "DSLs/Functions/describe.h"           // IWYU pragma: keep
#include "DSLs/Functions/it.h"                 // IWYU pragma: keep
#include "DSLs/Functions/set_timeout.h"        // IWYU pragma: keep
#include "DSLs/Functions/setup.h"              // IWYU pragma: keep
#include "DSLs/Functions/skip.h"               // IWYU pragma: keep
#include "DSLs/Functions/spec.h"               // IWYU pragma: keep
#include "DSLs/Functions/teardown.h"           // IWYU pragma: keep
#include "DSLs/Functions/test.h"               // IWYU pragma: keep
#include "DSLs/TopLevel/AsyncGroupSetup.h"     // IWYU pragma: keep
#include "DSLs/TopLevel/AsyncGroupTeardown.h"  // IWYU pragma: keep
#include "DSLs/TopLevel/AsyncSetup.h"          // IWYU pragma: keep
#include "DSLs/TopLevel/AsyncTeardown.h"       // IWYU pragma: keep
#include "DSLs/TopLevel/AsyncTest.h"           // IWYU pragma: keep
#include "DSLs/TopLevel/BeginTestGroup.h"      // IWYU pragma: keep
#include "DSLs/TopLevel/BeginTestTemplate.h"   // IWYU pragma: keep
#include "DSLs/TopLevel/ChildTestGroup.h"      // IWYU pragma: keep
#include "DSLs/TopLevel/Configure.h"           // IWYU pragma: keep
#include "DSLs/TopLevel/ConfigureFn.h"         // IWYU pragma: keep
#include "DSLs/TopLevel/DefineTemplate.h"      // IWYU pragma: keep
#include "DSLs/TopLevel/Describe.h"            // IWYU pragma: keep
#include "DSLs/TopLevel/DescribeFn.h"          // IWYU pragma: keep
#include "DSLs/TopLevel/EndTestGroup.h"        // IWYU pragma: keep
#include "DSLs/TopLevel/EndTestTemplate.h"     // IWYU pragma: keep
#include "DSLs/TopLevel/GroupSetup.h"          // IWYU pragma: keep
#include "DSLs/TopLevel/GroupSetupAsync.h"     // IWYU pragma: keep
#include "DSLs/TopLevel/GroupTeardown.h"       // IWYU pragma: keep
#include "DSLs/TopLevel/GroupTeardownAsync.h"  // IWYU pragma: keep
#include "DSLs/TopLevel/It.h"                  // IWYU pragma: keep
#include "DSLs/TopLevel/MetaData.h"            // IWYU pragma: keep
#include "DSLs/TopLevel/SetTestGroup.h"        // IWYU pragma: keep
#include "DSLs/TopLevel/SetTimeoutMs.h"        // IWYU pragma: keep
#include "DSLs/TopLevel/Setup.h"               // IWYU pragma: keep
#include "DSLs/TopLevel/SetupAsync.h"          // IWYU pragma: keep
#include "DSLs/TopLevel/Skip.h"                // IWYU pragma: keep
#include "DSLs/TopLevel/SkipAll.h"             // IWYU pragma: keep
#include "DSLs/TopLevel/Spec.h"                // IWYU pragma: keep
#include "DSLs/TopLevel/SpecAsync.h"           // IWYU pragma: keep
#include "DSLs/TopLevel/Specs.h"               // IWYU pragma: keep
#include "DSLs/TopLevel/SpecsFn.h"             // IWYU pragma: keep
#include "DSLs/TopLevel/StartTestGroup.h"      // IWYU pragma: keep
#include "DSLs/TopLevel/StartTestTemplate.h"   // IWYU pragma: keep
#include "DSLs/TopLevel/Tag.h"                 // IWYU pragma: keep
#include "DSLs/TopLevel/Tags.h"                // IWYU pragma: keep
#include "DSLs/TopLevel/Teardown.h"            // IWYU pragma: keep
#include "DSLs/TopLevel/TeardownAsync.h"       // IWYU pragma: keep
#include "DSLs/TopLevel/Test.h"                // IWYU pragma: keep
#include "DSLs/TopLevel/TestAsync.h"           // IWYU pragma: keep
#include "DSLs/TopLevel/TestGroup.h"           // IWYU pragma: keep
#include "DSLs/TopLevel/TestGroupFn.h"         // IWYU pragma: keep
#include "DSLs/TopLevel/TestTemplate.h"        // IWYU pragma: keep
#include "DSLs/TopLevel/TestTemplateFn.h"      // IWYU pragma: keep
#include "DSLs/TopLevel/UnsetTestGroup.h"      // IWYU pragma: keep
#include "DSLs/TopLevel/UseTemplate.h"         // IWYU pragma: keep
#include "DSLs/TopLevel/UseTemplates.h"        // IWYU pragma: keep

using SpecDone = SpecsCpp::SpecDone;

using namespace SpecsCpp::DSLs::Functions;
