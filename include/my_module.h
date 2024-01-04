// hi from foo

//@ module;

//@ import my_module;
#include <iostream>  // @headerunit@
#include <string>    // @nomodule@
#include <vector>    // @module@

//@ export module my_module;

//@ export @//
namespace foo {
    void bar() { std::cout << "hi from foo" << std::endl; }
}