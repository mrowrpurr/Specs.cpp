# 💲 Test Variables

Sometimes you may find yourself needing to share data between your `Setup`, `Teardown`, and `Test` code.

`Specs` provides a way to define, update, and access variables which are stored on the currently running `Test`.

> **Important:** any variables still remaining in the test variable collection after the final `Teardown` will be `delete`'d.

```cpp
#define SPEC_GROUP My_Tests

#include <Specs.h>

Setup {
    // Add any simple types
    current_test->var("number", 42);
    current_test->var("bool value", true);

    // Or pointers to complex types
    current_test->var("dog", new Dog());

    // Use var_text() for strings
    current_test->var_text("text", "Hello World!");
}

Test("My Test") {
    auto number = current_test->var<int>("number");
    auto boolean = current_test->var<bool>("bool value");
    auto* pointer = current_test->var<Dog*>("dog");
    auto text = current_test->var_text("text");
}
```
