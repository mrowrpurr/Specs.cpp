// hi from foo

module;

import my_module;
import <iostream>;

import vector;

export module my_module;

export namespace foo {
    void bar() { std::cout << "hi from foo" << std::endl; }
}