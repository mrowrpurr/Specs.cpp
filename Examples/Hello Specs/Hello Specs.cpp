#define SPEC_GROUP Hello_Hello

#include "SpecHelper.h"  // IWYU pragma: keep

class Dog {
public:
    Dog() { _Log_("Dog is being created"); }
    ~Dog() { _Log_("Dog is being destroyed"); }
};

Setup { current_test->var("dog", new Dog()); }

Test("Foo") {
    //
    _Log_("This test is {} in group {}", current_test->description(), current_group->description());
}

Describe("Describe 1") {
    test("test 1", []() { _Log_("test 1"); });

    skip();
    test("test 2", []() { _Log_("test 2"); });
}

StartTestGroup("Child Group") {
    // Any Setup/Teardown/Test defined here will be added to the:
    // [Tests One] > [Child Group] group
    Setup { /* Setup code goes here... */
    }
    Teardown { /* Teardown code goes here... */
    }
    Test("Test something") { /* Test code goes here... */
    }

    StartTestGroup("Different Group") {
        // Any Setup/Teardown/Test defined here will be added to the:
        // [Tests One] > [Child Group] > [Different Group] group
        Setup { /* Setup code goes here... */
        }
        Teardown { /* Teardown code goes here... */
        }
        Test("Test something else") { /* Test code goes here... */
        }
    }
    EndTestGroup();
}
EndTestGroup();
