module;

#include <Specs/v3/Interfaces.h>

#include <string>

export module specs.application;

export namespace SpecsCpp::v3 {
    // struct ExampleInterfaceImplementation : public IExampleInterface {};

    std::string SayHello() { return "Hello!"; }
}
