#define spec_file Spec_file_header_test

#include "SpecHelper.h"  // IWYU pragma: keep

Test("THIS IS IN THE SPEC FILE") { _Log_("Hello from THE SPEC_FILE"); }

Setup { _Log_("Setup for EVERYONE!"); }
