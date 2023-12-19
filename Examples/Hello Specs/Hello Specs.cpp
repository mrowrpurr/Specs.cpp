#define spec_name HelloSpecs

#include "SpecHelper.h"  // IWYU pragma: keep

Teardown { _Log_("Hello from Teardown"); }

GroupSetup { _Log_("Hello from GroupSetup"); }

GroupTeardown { _Log_("Hello from GroupTeardown"); }

Test("Test One") { _Log_("Hello from Test One"); }

Test("Test Two") { _Log_("Hello from Test Two"); }

Test("Test Three") { _Log_("Hello from Test Three"); }

TestGroup("Group 2");

Test("Test Four") { _Log_("Hello from Test Four"); }
