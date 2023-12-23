# 🎓 Writing Tests

[TOC]

It's time to write your first tests!

> _This assumes that you have completed the steps outlines in [Installing Specs](Installing.md)_

This page will cover:

- Creating a project
- Creating test files
- Defining tests with `Test` and `TestAsync`
- Defining setup and teardown code with `Setup` and `Teardown`
- Defining groups of tests with `TestGroup` and `Describe`

> For more detailed information on the syntax of the test files, see [Syntax Reference](SyntaxReference.md)

# Creating a project

To create tests, you will need to either:
- Create a binary/executable project (_the tests will run when you run the executable_)
- Create a shared library (_a separate `Specs.exe` test runner can load multiple shared libraries of tests_)

## Entrypoint

Create a new file named `main.cpp`.

Assuming you are creating a binary project, add the following code to `main.cpp`:

```cpp
#include <Specs/Main.h>
```

This will define the `main()` entrypoint for the executable.

If you are creating a shared library, add the following code to `main.cpp`:

```cpp
#include <Specs/SharedLibrary.h>
```

This will define the entrypoint function used by the `Specs` test loader, e.g. when loading one or more shared libraries of tests from a `Specs.exe` test runner.

> To learn more about grouping specs into shared libraries, see [Shared Libraries](SharedLibraries.md)

> 💡 **Tip:** If you are using `snowhouse`, you should `#include <Specs/Snowhouse/Setup.h>` in your main binary or shared library `.cpp` file.

# Creating test files

Now you are ready to define a file with one or more tests.

Create a new file named `MyFirstTests.cpp`.

Add the following code to `MyFirstTests.cpp`:

```cpp
#define spec_name My_First_Tests

#include <Specs.h>

// Tests go here...
```

This defines a new group of tests with the description `"My First Tests"`.

Any tests defined in this file will be added to this group.

## Test file #define header

Every `.cpp` file containing tests must have one of these unique `#define` at the top of the file:

- `#define spec_context UNIQUE_NAME`
- `#define spec_file UNIQUE_NAME`
- `#define spec_name UNIQUE_NAME`
- `#define spec_template UNIQUE_NAME`

### #define spec_context

Using `#define spec_context UNIQUE_NAME` will ensure that the `Test`, `Setup`, `Teardown`, `etc` macros defined in this file do not conflict with macros defined in other files.

That's it, though. The content in your file might be added to a group of tests from _another file_, because `spec_context` does not define a group nor does it clear the currently active group.

**Use of `spec_context` is not recommended.**

### #define spec_file

If you `#define spec_file UNIQUE_NAME`, then the tests in the file are added to a global group.

The tests (_and setup/teardown code_) in this file will be run for all tests.

This could be useful for defining global setup/teardown code:

```cpp
#define spec_file Global_Setup_Teardown

#include <Specs.h>

Setup() {
    // Global setup code goes here...
}

Teardown() {
    // Global teardown code goes here...
}
```

### #define spec_name

If you `#define spec_name UNIQUE_NAME`, then the tests in the file are added to a group with the description of `UNIQUE_NAME`.

> _Note: underscores in `UNIQUE_NAME` are replaced with spaces in the description._

This is a good way to define a group of tests that are related to each other.

```cpp
#define spec_name My_Tests_About_Some_Feature

#include <Specs.h>

// Tests go here...
```

And, for example, in another file...

```cpp
#define spec_name My_Tests_About_Another_Feature

#include <Specs.h>

// Tests go here...
```

### #define spec_template

`Specs` supports defining templates.

> To learn more about templates, see [Shared Code Templates](Templates.md)

Templates are a way of defining `Setup` and `Teardown` and `Test` code that can be shared and reused by multiple test groups.

If you `#define spec_template UNIQUE_NAME`, then the tests in the file are added to a template with the description of `UNIQUE_NAME`.

> _Note: underscores in `UNIQUE_NAME` are replaced with spaces in the description._

This is a good way to define a template that can be used by multiple test groups.

```cpp
#define spec_template My_Shared_Setup_And_Teardown

#include <Specs.h>

Setup() {
    // Shared setup code goes here...
}

Teardown() {
    // Shared teardown code goes here...
}
```

And then, in another test file...

```cpp
#define spec_name My_Tests_About_Some_Feature

#include <Specs.h>

// This imports the shared Setup/Teardown/etc into this group
UseTemplate("My Shared Setup And Teardown");

// Tests go here...
```

# Tests

Creating tests is easy!

Each test simply needs a description and a body.

```cpp
Test("Test Something!") {
    // Test code and assertions go here...
}
```

That's it!

# Asynchronous Tests

Creating tests with long-running code is just as easy!

```cpp
TestAsync("Test Something Async!") {
    // Test code and assertions go here...
    
    // Once your code is done, call `done()` to mark the test as finished.
    done();
}
```

If an asynchroneous test does not call `done()` within a configurable timeout, the test will fail with a timeout error.

> ℹ️ Timeout milliseconds can be configured via the `-t/--timeout` option

# Test assertions

Tests aren't particularly useful without assertions!

`Specs` provides built-in support for catching exceptions thrown during test execution.

```cpp
Test("Test Something!") {
    if (1 != 2)
        throw "Expected 1 to equal 2!";
}
```

```
[FAILED] Test Something!

Expected 1 to equal 2!

1 failed
```

Any exceptions thrown during test execution will be caught and reported as a failure.

The following exception types have special handling:

- `std::exception` (_and derived types_)
  - The `what()` message is reported as the failure message
- C strings (`const char*`)
  - The string is reported as the failure message

Any other exception types will be reported as a failure with a basic message like `Unknown exception`.

It is recommended to use `Specs` with an assertion library, such as `snowhouse` or `libassert`.

## Snowhouse assertions

> For instructions on installing `snowhouse` with the `Specs` adapter, see [Installing Specs](Installing.md)
>
> **Reminder:** your `main.cpp` needs to include `<Specs/Snowhouse/Setup.h>` to enable the `snowhouse` adapter.

When the `Specs` adapter for `snowhouse` is included, you can use `snowhouse` assertions in your tests.

```cpp
#include <Specs.h>
#include <Specs/Snowhouse.h>

Test("Test Something!") {
    AssertThat(69, Equals(420));
}
```

```
[FAILED] Test Something!

Expected: equal to 420
Actual: 69

[Test.cpp:5] AssertThat(69, Equals(420));

1 failed
```

Failed `snowhouse` assertions will be reported as failures, including:
- The snowhouse assertion failure message
- The file and line number where the assertion failed
- A preview of the line of code responsible for the assertion

## libassert assertions

> For instructions on installing `libassert` with the `Specs` adapter, see [Installing Specs](Installing.md)
>
> **Reminder:** the `assert()` macro does not work in `release` mode. Recommended: use `assert_that` instead.

When the `Specs` adapter for `libassert` is included, you can use `libassert` assertions in your tests.

```cpp
#include <Specs.h>
#include <Specs/LibAssert.h>

Test("Test Something!") {
    assert_that(69 == 420);
}
```

```
[FAILED] Test Something!

Verification failed at FooTest.cpp:5: void __cdecl __globalMacroFunctions__function___SPEC_TEST__DefaultCompilationUnit_0(SpecsCpp::ISpec *):
    VERIFY(69 == 420);

1 failed
```

Failed `libassert` assertions will be reported as failures, including:
- The file and line number where the assertion failed
- A preview of the line of code responsible for the assertion


# Setup and Teardown

Every test group supports the following:

- `Setup`: Runs before each test in the group
- `Teardown`: Runs after each test in the group
- `OneTimeSetup`: Runs once before the first test in the group
- `OneTimeTeardown`: Runs once after the last test in the group

Test groups can define as many of each of these as desired.

If you nest test groups, this is the order of operations:

- The `OneTimeSetup` of the outermost group is run
- The `OneTimeSetup` of each nested group is run
- The `Setup` of the outermost group is run
- The `Setup` of each nested group is run
- The `Test` of each nested group is run
- The `Teardown` of each nested group is run
- The `Teardown` of the outermost group is run
- The `OneTimeTeardown` of each nested group is run

If any `Setup` fails:

- the rest of the `Setup` in that group are skipped
- the `Test` in that group is skipped
- the `Teardown` are still all executed
- if this `Setup` is in a nested group, the `Teardown` of the outermost group are still executed

```cpp
#include <Specs.h>

OneTimeSetup { /* This runs once before the first test in this group */ }

OneTimeTeardown { /* This runs once after the last test in this group */ }
OneTimeTeardown { /* More stuff to teardown after the group has run */ }

Setup { /* This runs before each test in this group */ }
Setup { /* This ALSO runs before each test in this group */ }
Setup { /* You can have as many of these as you like */ }

TearDown { /* This runs after each test in this group */ }
Teardown { /* You can have as many of these as you like too */ }

Test("Test Something!") {
    // Test code and assertions go here...
}
```

## Asynchronous Setup and Teardown

All of the setup and teardown macros support Asynchronous code:

- `SetupAsync`
- `TeardownAsync`
- `OneTimeSetupAsync`
- `OneTimeTeardownAsync`

These work identically to `TestAsync`, which must call `done()` to mark the setup/teardown as finished.

```cpp
#include <Specs.h>

OneTimeSetupAsync {
    // Async setup code goes here...
    done();
}

OneTimeTeardownAsync {
    // Async teardown code goes here...
    done();
}

SetupAsync {
    // Async setup code goes here...
    done();
}

TeardownAsync {
    // Async teardown code goes here...
    done();
}

Test("Test Something!") {
    // Test code and assertions go here...
}

TestAsync("Test Something Async!") {
    // Test code and assertions go here...
    done();
}
```

# Test Groups

Grouping your tests is a critical part of writing tests.

It is recommended to use `#define spec_name UNIQUE_NAME` to define a group for each `.cpp` file containing tests.

## Unique test group for each file

`TestsOne.cpp`

```cpp
#define spec_name Tests_One

#include <Specs.h>

Test("Test 1") {
    // Test code and assertions go here...
}
```

`TestsTwo.cpp`

```cpp
#define spec_name Tests_Two

#include <Specs.h>

Test("Test 2") {
    // Test code and assertions go here...
}
```

In the above code:

- `Tests_One` is a defined as a group containing one test named `Test 1`
- `Tests_Two` is a defined as a group containing one test named `Test 2`

This works great, but what if you want to group your tests into sub-groups?

## Nesting child groups

Once you need to define sub-groups, there are 2 separate syntaxes to choose from:

1. `TestGroup` defines a new top-level group (_within the file group defined via spec_name_)
2. `BeginTestGroup`/`EndTestGroup` define nested groups
3. `Describe` defines a nested group and child tests/groups/setups/teardowns are defined using a lambda syntax

### TestGroup

### BeginTestGroup / EndTestGroup

### Describe
