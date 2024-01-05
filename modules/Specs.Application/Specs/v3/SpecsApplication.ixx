module;



#include <string>

export module specs.application;
import specs.interfaces;

export namespace SpecsCpp::v3 {
    struct ExampleInterfaceImplementation : public IExampleInterface {
        int GetNumber() override { return 69; }
    };

    std::string SayHello() { return "Hello!"; }
}
