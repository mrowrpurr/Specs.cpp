#include "SpecHelper.h"
#include "RunHelper.h"

#if defined(CORE_SPECS)
    #include "Core/SomeThing.Spec.h"
#elif defined(OTHER_SPECS)
    // include other ones
#endif

int main(int argc, char* argv[]) { return runSpecs(argc, argv); }
