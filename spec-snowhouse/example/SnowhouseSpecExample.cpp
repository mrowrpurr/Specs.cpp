#include <Spec/Autorun.h>
#include <Spec/Snowhouse.h>

#include <iostream>

using namespace Spec;
using namespace snowhouse;

class CustomException {};

Test("Passing test") { std::cout << "This should pass!" << std::endl; }

Test("Failing test (snowhouse assertion)") {
    std::cout << "This should fail SNOWHOUSE!" << std::endl;
    AssertThat(69, Equals(420));
    std::cout << "This should not run!" << std::endl;
}

Test("Failing test (throw a string)") {
    std::cout << "This should fail STRING!" << std::endl;
    throw std::string("This is a string exception!");
    std::cout << "This should not run!" << std::endl;
}

Test("What about a custom exception?") {
    Print("Gonna throw custom...");
    throw CustomException();
}
