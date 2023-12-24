# 💲 Test Variables

[TOC]

# Using Variables

Sometimes you may find yourself needing to share data between your `Setup`, `Teardown`, and `Test` code.

`Specs` provides a way to define, update, and access variables which are stored on the currently running `Test`.

> **Important:** any variables still remaining in the test variable collection after the final `Teardown` for that test will be `delete`'d.

```cpp
#define SPEC_GROUP My_Tests

#include <Specs.h>

Setup {
    // Add any simple types
    current_test->var("number", 42);
    current_test->var("value", true);

    // Or pointers to complex types
    current_test->var("dog", new Dog());

    // Use var_text() for text (const char*)
    current_test->var_text("text", "Hello World!");
}

Test("My Test") {
    // Access variables in tests via current_test->var<T>()
    auto number = current_test->var<int>("number");
    auto value  = current_test->var<bool>("value");
    auto* dog   = current_test->var<Dog*>("dog");
    auto text   = current_test->var_text("text");
}

Teardown {
    // Variables can also be accessed in teardowns
    // via current_test->var<T>()
}
```

## Setting Variables

Use `current_test->var()` to set variables on the currently running `Test`:

```cpp
#define SPEC_GROUP My_Tests

#include <Specs.h>

Setup {
    current_test->var("NAME", value);
}
```

### Simple Values

For simple values (`int`, `bool`, `float`, etc.) you can use `current_test->var(<variable name>, value)`:

```cpp
current_test->var("number", 42);
current_test->var("value", true);
current_test->var("pi", 3.14159f);
```

### Text

For text (`const char*`), use `current_test->var_text(<variable name>, "text")`:

```cpp
curent_test->var_text("text", "Hello World!");
```

> The `var_text` function manages memory for copying and storing `const char*` values.

### Complex Types

For complex types, you should use `current_test->var(<variable name>, *pointer)` with a pointer to the instance:

```cpp
current_test->var("dog", new Dog());
```

```cpp
// Somewhere in your code...
Dog* dog = new Dog();

current_test->var("dog", dog);
```

## Getting Variables

When accessing variables, you must specify the type of the variable you are trying to access:

```cpp
auto number = current_test->var<int>("number");
auto value  = current_test->var<bool>("value");
auto pi    = current_test->var<float>("pi");
auto* dog   = current_test->var<Dog*>("dog");
```

### Text

To access text (`const char*`), use `current_test->var_text(<variable name>)`:

```cpp
auto* text = current_test->var_text("text");
```

## Unsetting Values

If you want to remove a variable from the variable collection, you can use `current_test->unset(<variable name>)`:

```cpp
current_test->unset("number");
```

## Variable Lifetime

By default, every variable set on a `Test` will be `delete`'d after the final `Teardown` for that is run.

You can override this behavior by passing a value for the `bool destructable` parameter of `var()`:

```cpp
// Somewhere in your code...
Dog* dog = new Dog();

// ...

// When we set this variable to the pointer of a Dog,
// we do NOT want the Dog to be deleted by the tests!
current_test->var("dog", dog, false);
```

The above example will not `delete` the `Dog` instance when the test is finished.

### Variable lifetime helpers

If you want to more explicit than passing `false`, the following helpers exist:
- `current_test->managed_var(<variable name>, value)`
- `current_test->unmanaged_var(<variable name>, value)`

#### managed_var

The `managed_var` function is equivalent to the default behavior of `var()`.

When using `managed_var`, the value will be automatically deleted after the final `Teardown` for the test is run.

#### unmanaged_var

When using `unmanaged_var`, the value will **not** be deleted after the final `Teardown` for the test is run.

```cpp
// Somewhere in your code...
Dog* dog = new Dog();

// ...

// When we set this variable to the pointer of a Dog,
// we do NOT want the Dog to be deleted by the tests!
current_test->unmanaged_var("dog", dog);
```

### Editing the lifetime of a variable

You can change the "destructable" property of a variable by using `current_test->set_destructable(<variable name>, <bool>)`:

```cpp
current_test->var("dog", new Dog());
current_test->set_destructable("dog", false);
```

> If you ever need to check the "destructable" property of a variable, you can use `current_test->is_destructable(<variable name>)`.
