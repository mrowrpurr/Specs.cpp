// hi from foo

//@ module;

#include <iostream>

//@ export module my_module;

//@ export @//
namespace foo {
    void bar() { std::cout << "hi from foo" << std::endl; }
}