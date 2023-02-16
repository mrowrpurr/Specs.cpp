#include <Spec/Autorun.h>
#include <snowhouse/snowhouse.h>

#include <iostream>


using namespace Spec;
using namespace snowhouse;

Test("Passing test") { std::cout << "This should pass!" << std::endl; }

Test("Failing test") {
    std::cout << "This should fail!" << std::endl;
    AssertThat(69, Equals(420));
    std::cout << "This should not run!" << std::endl;
}
