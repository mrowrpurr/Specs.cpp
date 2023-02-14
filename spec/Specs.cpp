#include <Spec/Autorun.h>

using namespace Spec;

Test("This should pass") {}
Test("This should fail") { throw "KABOOM!"; }
Test("This should also fail") { throw std::runtime_error("Runtime FAILURE!"); }
