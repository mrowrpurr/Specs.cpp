#define spec_file Multiple_Templates

#include "SpecHelper.h"  // IWYU pragma: keep

DefineTemplate("Template A");

// Setup { _Log_("Hello from Setup in TEMPLATE A"); }

TestTemplateFn(Template_B);

// Setup { _Log_("Hello from Setup in TEMPLATE B"); }
