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

## Test Assertions

# Asyncronous Tests

# Setup and Teardown

## Asyncronous Setup and Teardown

# Test Groups
