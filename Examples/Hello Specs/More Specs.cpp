#define spec_name More_Specs

#include "SpecHelper.h"  // IWYU pragma: keep

TestGroup("Group 1");

UseTemplates("Template A", "Template_B");

Test("Test One") { _Log_("Hello from Test One"); }

Test("Test Two") { _Log_("Hello from Test Two"); }

Test("Test Three") { _Log_("Hello from Test Three"); }

TestGroup("Group 2");

UseTemplate("The_Template_Name");

Test("Test Four") { _Log_("Hello from Test Four"); }
