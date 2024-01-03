#include <Specs.h>
#include <Specs/V3/Entrypoint.h>

using namespace SpecsCppV3;

Example("Run the Specs main() entrypoint") {
    SpecsEntrypoint entrypoint;
    entrypoint.main();

    // ... test that it printed something to STDOUT
}
