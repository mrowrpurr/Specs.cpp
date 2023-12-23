#define spec_name Multiple_Groups_with_Nesting

#include "SpecHelper.h"  // IWYU pragma: keep

Setup { _Log_("Hello from Setup"); }
Test("Test One") { _Log_("Hello from Test One"); }

TestGroup("Child Group 1");

Setup { _Log_("Hello from Child Group 1 Setup"); }
Test("Child Group 1 Test") { _Log_("Hello from Child Group 1 Test"); }

BeginTestGroup("Nested Child Group");
Setup { _Log_("Hello from Nested Child Group Setup"); }
Test("Nested Child Group Test") { _Log_("Hello from Nested Child Group Test"); }

BeginTestGroup("Nested Nested Child Group");
Setup { _Log_("Hello from Nested Nested Child Group Setup"); }
Test("Nested Nested Child Group Test") { _Log_("Hello from Nested Nested Child Group Test"); }
EndTestGroup();  // Nested Nested Child Group

Test("Nested Child Group Test 2") { _Log_("Hello from Nested Child Group Test 2"); }
EndTestGroup();  // Nested Child Group

Test("Child Group 1 Test 2") { _Log_("Hello from Child Group 1 Test 2"); }
UnsetTestGroup();  // Child Group 1

Test("Test Two") { _Log_("Hello from Test Two"); }
