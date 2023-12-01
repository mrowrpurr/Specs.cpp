#pragma once

#include <Specs/SpecDone.h>

#include "DSLs/Functions/describe.h"      // IWYU pragma: keep
#include "DSLs/Functions/it.h"            // IWYU pragma: keep
#include "DSLs/Functions/setup.h"         // IWYU pragma: keep
#include "DSLs/Functions/teardown.h"      // IWYU pragma: keep
#include "DSLs/Functions/test.h"          // IWYU pragma: keep
#include "DSLs/TopLevel/Configure.h"      // IWYU pragma: keep
#include "DSLs/TopLevel/Describe.h"       // IWYU pragma: keep
#include "DSLs/TopLevel/It.h"             // IWYU pragma: keep
#include "DSLs/TopLevel/Setup.h"          // IWYU pragma: keep
#include "DSLs/TopLevel/SetupAsync.h"     // IWYU pragma: keep
#include "DSLs/TopLevel/Spec.h"           // IWYU pragma: keep
#include "DSLs/TopLevel/SpecAsync.h"      // IWYU pragma: keep
#include "DSLs/TopLevel/Teardown.h"       // IWYU pragma: keep
#include "DSLs/TopLevel/TeardownAsync.h"  // IWYU pragma: keep
#include "DSLs/TopLevel/Test.h"           // IWYU pragma: keep
#include "DSLs/TopLevel/TestAsync.h"      // IWYU pragma: keep
#include "DSLs/TopLevel/TestGroup.h"      // IWYU pragma: keep

using SpecDone = SpecsCpp::SpecDone;
