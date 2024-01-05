#define SPEC_FILE CallFunctionTest

#include <Specs.h>


#include <iostream>

import specs.application;

Test("Call function in Specs.Application") {
    //
    auto functionResult  = SpecsCpp::v3::SayHello();
    auto impl            = SpecsCpp::v3::ExampleInterfaceImplementation();
    auto interfaceResult = impl.GetNumber();
    std::cout << "functionResult: " << functionResult << std::endl;
    std::cout << "interfaceResult: " << interfaceResult << std::endl;
}
