#define spec_file HelloSpecs

#include "SpecHelper.h"  // IWYU pragma: keep

class DestroyMe {
public:
    DestroyMe() { _Log_("DestroyMe::DestroyMe()"); }
    ~DestroyMe() { _Log_("DestroyMe::~DestroyMe()"); }
};

Setup {
    current_spec->var("answer", 42);
    current_spec->var_text("c-string", "Hello, World!");
    current_spec->var("destroy_me", new DestroyMe());
}

Test("First test") {
    //
    _Log_("The answer is {}", current_spec->var<int>("answer"));
    _Log_("The c-string is {}", current_spec->var_text("c-string"));
}

Test("Second Test") {
    //
}
