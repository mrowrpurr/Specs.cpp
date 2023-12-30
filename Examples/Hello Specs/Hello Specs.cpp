#define SPEC_GROUP Hello_Hello

#include "SpecHelper.h"  // IWYU pragma: keep

Setup {
    _Log_("HI FROM SETUP !!!!!!!!!! defined in {}", current_setup->group()->full_description());
}

UseTemplate("MyTemplate");
