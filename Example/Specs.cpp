#include <Spec/Autorun.h>

Test("This should pass") { Print("Pass!"); }
Test("This should fail") {
    throw "KABOOM!";
    Print("Fail!");
}
Test("This should fail with an exception") {
    throw std::runtime_error("KABOOM exception!");
    Print("Fail!");
}