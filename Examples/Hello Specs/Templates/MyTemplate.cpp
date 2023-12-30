#define SPEC_TEMPLATE MyTemplate

#include "SpecHelper.h"

Setup { _Log_("Setup inside of {}", current_setup->group()->full_description()); }

Test("THIS IS A TEST from the template") {}
Test("THIS IS another TEST from the template") {}
