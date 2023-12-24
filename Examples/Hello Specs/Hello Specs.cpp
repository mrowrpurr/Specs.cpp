#define SPEC_GROUP Hello_Hello

#include "SpecHelper.h"  // IWYU pragma: keep

// TODO double check that .var("test", "foo") doesn't "just work"

class Dog {
    std::string _name;

public:
    Dog(std::string_view name) : _name(name) { _Log_("Dog is being created"); }
    ~Dog() { _Log_("Dog is being destroyed"); }
    std::string name() const { return _name; }
};

Setup {
    current_test->var("num", 69);
    current_test->var("dog", new Dog("Rover"));
    current_test->var_text("text", "Hello World");
}

Test("Foo") {
    //
    _Log_("NUM: {}", current_test->var<int>("num"));
    _Log_("TEXT: {}", current_test->var_text("text"));
    _Log_("DOG: {}", current_test->var<Dog*>("dog")->name());
}
