<img src="Resources/Images/Logo_400.png" align="right">

# Specs

> **Beautiful C++ Test Framework**
>
> - _Syntax is simple and configurable_
> - _Supports asyncronous tests_
> - _Supports runnings tests from shared libraries_
> - _Supports any C++ assertion library_ (e.g. `snowhouse` or `libassert`)

---

# What?

C++ test framework with simple syntax which supports async tests.

```cpp
#include <Specs.h>

TestGroup("My Tests");

Setup { /* Setup Code */ }
Teardown { /* Teardown Code */ }

Test("Something") {
    assert(69 == 420);
    AssertThat(69, Equals(69));
}

TestAsync("Slow things") {
    // Do something slow...
    done();
}
```

# Why?

1. I enjoy authoring testing frameworks.
2. I wanted very simple, readable syntax for tests.
3. I wanted to use existing assertion libraries.
4. I needed to write async tests.
5. I needed to be able to load and run tests from shared libraries.

> _I'm proud of the result and I hope you enjoy using it!_

# Table of Contents

- [Specs](#specs)
- [What?](#what)
- [Why?](#why)
- [Table of Contents](#table-of-contents)
- [Installation](#installation)
  - [xmake](#xmake)
    - [Basic Install](#basic-install)
      - [`xmake.lua`](#xmakelua)
    - [With Assertion Library Integration](#with-assertion-library-integration)
      - [`xmake.lua`](#xmakelua-1)
  - [vcpkg / CMake](#vcpkg--cmake)
    - [`CMakeLists.txt`](#cmakeliststxt)
    - [`vcpkg.json`](#vcpkgjson)
    - [`vcpkg-configuration.json`](#vcpkg-configurationjson)
    - [`libassert`](#libassert)
- [`Specs.cpp` Usage Documentation](#specscpp-usage-documentation)
  - [Creating Test Files](#creating-test-files)
    - [Single test file](#single-test-file)
      - [`MySpecs.cpp`](#myspecscpp)
    - [Multiple .cpp test files](#multiple-cpp-test-files)
      - [`main.cpp`](#maincpp)
      - [`MySpecs.One.cpp`](#myspecsonecpp)
      - [`MySpecs.Two.cpp`](#myspecstwocpp)
  - [Choosing Assertion Library](#choosing-assertion-library)
    - [Using Snowhouse assertions](#using-snowhouse-assertions)
    - [Using libassert assertions](#using-libassert-assertions)
  - [Test Syntax Styles](#test-syntax-styles)
    - [Top-Level Macros](#top-level-macros)
      - [One Test Group](#one-test-group)
      - [Multiple Test Groups](#multiple-test-groups)
    - [Lambda Functions](#lambda-functions)
      - [Without `spec_file` define](#without-spec_file-define)
  - [Command-Line Options](#command-line-options)
    - [Filtering Tests by Name](#filtering-tests-by-name)
    - [Random Ordering](#random-ordering)
    - [Loading Tests from Shared Libraries (`.dll/.so`)](#loading-tests-from-shared-libraries-dllso)
      - [Define specs in a shared library](#define-specs-in-a-shared-library)
        - [`MySpecs.cpp`](#myspecscpp-1)
  - [Setup and Teardown](#setup-and-teardown)
    - [Top-Level Setup and Teardown](#top-level-setup-and-teardown)
    - [Setup and Teardown inside groups](#setup-and-teardown-inside-groups)
  - [Async Tests](#async-tests)
- [Syntax](#syntax)
  - [Available Built-in Syntax](#available-built-in-syntax)
    - [`Test("...") { ... }`](#test---)
    - [`TestAsync("...") { ...; done() }`](#testasync---done-)
    - [`TestGroup("...");`](#testgroup)
    - [`UnsetTestGroup();`](#unsettestgroup)
    - [`Setup { ... }`](#setup---)
    - [`Teardown { ... }`](#teardown---)
    - [`Config { ... }`](#config---)
    - [`Configure(UniqueToken) { ... }`](#configureuniquetoken---)
    - [`Describe("...") { ... }`](#describe---)
    - [`DescribeFn(UniqueToken) { ... }`](#describefnuniquetoken---)
    - [`test("...", []() { ... });`](#test----)
    - [`test("...", [](auto done) { ...; done(); });`](#test-auto-done---done-)
    - [`setup([]() { ... });`](#setup----1)
    - [`setup([](auto done) { ...; done(); });`](#setupauto-done---done-)
    - [`teardown([]() { ... });`](#teardown----1)
    - [`teardown([](auto done) { ...; done(); });`](#teardownauto-done---done-)
    - [`describe("...", []() { ... });`](#describe----)
  - [Choosing Available Syntax](#choosing-available-syntax)
  - [Build Your Own Syntax](#build-your-own-syntax)
  - [Exception Handling](#exception-handling)
    - [Create Custom Exception Handler](#create-custom-exception-handler)
- [Spec Reporters](#spec-reporters)
  - [Specifying reporter(s) via command-line](#specifying-reporters-via-command-line)
  - [Default Console Reporter](#default-console-reporter)
  - [JUnit XML Reporter](#junit-xml-reporter)
  - [TAP Console Reporter](#tap-console-reporter)
  - [Create Custom Reporter](#create-custom-reporter)
- [Spec Runners](#spec-runners)
  - [Specifying runner via command-line](#specifying-runner-via-command-line)
  - [Default Runner](#default-runner)
  - [Parallel Runner](#parallel-runner)
  - [Create Custom Runner](#create-custom-runner)
- [Spec Introspection / Data Model](#spec-introspection--data-model)
- [TODO Wishlist](#todo-wishlist)
- [License](#license)


# Installation

## xmake

### Basic Install

This is a barebones `Specs.cpp` installation with no assertion library integration.

With this setup, any `std::exception` (_or literal string_) thrown will be caught and displayed as a test failure message.

#### `xmake.lua`

```lua
add_repositories("MrowrLib https://github.com/MrowrLib/Packages.git")

add_requires("specs")

target("MySpecs")
    set_kind("binary")
    add_packages("specs")
    add_files("*.cpp")
```

### With Assertion Library Integration

We provide integrations for the `snowhouse` and `libassert` assertion libraries.

See [Create Custom Exception Handler](#create-custom-exception-handler) for more information on how to create your own custom exception handler.

#### `xmake.lua`

```lua
add_repositories("MrowrLib https://github.com/MrowrLib/Packages.git")

add_requires("specs")

-- For integration with snowhouse assertion library:
add_requires("vcpkg::snowhouse", "specs_snowhouse")

-- For integration with libassert assertion library:
add_requires("libassert_latest", { configs = { lowercase = true } })
add_requires("specs_libassert")

target("MySpecs")
    set_kind("binary")
    add_packages("specs")
    add_files("*.cpp")

    -- For integration with snowhouse assertion library:
    add_packages("vcpkg::snowhouse", "specs_snowhouse")

    -- For integration with libassert assertion library:
    add_packages("libassert_latest", "specs_libassert")
```

> _Note: as of 12/1/23 the `libassert` xmake package wasn't working for me, so I hosted `libassert_latest` on the `MrowrLib` xmake package registry which uses the latest version from GitHub and currently works for me._

For `snowhouse` or `libassert` integration, you need to "_bring your own_" version of the library. They are not automatic dependencies of the specs integration packages (_to not lock you into a specific version of these libraries_).

## vcpkg / CMake

### `CMakeLists.txt`

```cmake
add_executable(MyTests tests.cpp)

# Find specs and link it to your target
find_package(specs CONFIG REQUIRED)
target_link_libraries(MyTests PRIVATE specs::specs)
```

Optionally, add `snowhouse` and the `specs` adapter for `snowhouse`:

```cmake
# Find snowhouse (header-only) and link it to your target
find_path(SNOWHOUSE_INCLUDE_DIRS "snowhouse/assert.h")
target_include_directories(MyTests PRIVATE ${SNOWHOUSE_INCLUDE_DIRS})

# Find and link the specs adapter for snowhouse
find_package(specs_snowhouse CONFIG REQUIRED)
target_link_libraries(MySpecs PRIVATE specs::specs_snowhouse)
```

### `vcpkg.json`

```json
{
    "dependencies": [
        "specs"
    ]
}
```

And if you want to use `snowhouse` assertions:

```json
{
    "dependencies": [
        "specs",
        "snowhouse",
        "specs-snowhouse"
    ]
}
```

### `vcpkg-configuration.json`

```json
{
    "default-registry": {
        "kind": "git",
        "repository": "https://github.com/microsoft/vcpkg.git",
        "baseline": "ff6867374598312866fecfc64736a334591ceace"
    },
    "registries": [
        {
            "kind": "git",
            "repository": "https://github.com/MrowrLib/Packages.git",
            "baseline": "bc470bd6c6344d04298cfebd432fd9046407eeb0",
            "packages": [
                "specs",
                "specs-snowhouse",
                "specs-libassert",
                "mrowr-specs-snowhouse",
                "mrowr-function-pointer",
                "mrowr-global-macro-functions",
                "mrowr-collections",
                "mrowr-log",
                "mrowr-string-format"
            ]
        }
    ]
}
```

> _Update the default-registry baseline to the latest commit from https://github.com/microsoft/vcpkg_  
> _Update the MrowrLib/Packages baseline to the latest commit from https://github.com/MrowrLib/Packages_

### `libassert`

While `libassert` is available in the public `xmake` package registry, it is not currently available via `vcpkg`.

You can read the [How To Use This Library](https://github.com/jeremy-rifkin/libassert?tab=readme-ov-file#how-to-use-this-library) section of the `libassert` GitHub README on ways to use the library.

Once you have it installed, the steps to use the `specs` adapter for `libassert` should be the same as those steps shown for `snowhouse` above.

# `Specs.cpp` Usage Documentation

## Creating Test Files

### Single test file

Example of using only a single test file for your test suite.

#### `MySpecs.cpp`

```cpp
// Provides main() entrypoint automatically
#include <Specs/Main.h>

// Include the main Specs framework
#include <Specs.h>

Test("Something") {
    // Test code goes here...
}
```

### Multiple .cpp test files

More common example of using multiple `.cpp` files for your test suite.

When using multiple files, `<Specs/Main.h>` can be included in a single file
which could be a spec file or its own separate file, e.g. `RunSpecs.cpp` or `main.cpp`.

#### `main.cpp`

```cpp
#include <Specs/Main.h>
```

#### `MySpecs.One.cpp`

When using multiple files, you MUST\* label each file with a `spec_file` identifier:

> \* _... unless you use the DescribeFn syntax as described below in [Without `spec_file` define](#without-spec_file-define)_

```cpp
#define spec_file One // <--- MUST be BEFORE the <Specs.h> include

#include <Specs.h>

Test("Something") {
    // Test code goes here...
}
```

#### `MySpecs.Two.cpp`

```cpp
#define spec_file Two

#include <Specs.h>

Test("Something Else") {
    // Test code goes here...
}
```

The `spec_file` define has a few aliases which you can use instead:
- `#define spec_file SpecOne`
- `#define spec_name SpecOne`
- `#define spec_context SpecOne`

Any of the above will work.

This define provides support for multiple `.cpp` files to use the top-level macros such as `Test`, `Setup`, and `Teardown` (_etc_).

> _Note: this is due to the fact that the `__COUNTER__` macro does not provide unique counts across multiple compilation units (`.cpp`)._

## Choosing Assertion Library

### Using Snowhouse assertions

```cpp
#include <Specs.h>
#include <Specs/Snowhouse.h>

Test("...") {
    AssertThat(69, Equals(420));
}
```

### Using libassert assertions

```cpp
#include <Specs.h>
#include <Specs/LibAssert.h>

Test("...") {
    assert(69 == 420);
}
```

## Test Syntax Styles

As you'll read more about in the [Syntax](#syntax) section, there are a few different syntax styles available for defining tests.

To customize the available style syntax, see [Choosing Available Syntax](#choosing-available-syntax).

### Top-Level Macros

#### One Test Group

One test group per file using `TestGroup` and multiple top-level `Test` macros.

> The `Test` macro has built-in aliases: `Spec` and `It`.

```cpp
// spec_file is only required if you mave multiple separate .cpp files containing tests
#define spec_file MySpecs

#include <Specs.h>

// Important
// Without this, Setup/Teardown will run across ALL of your test files
// This scopes everything in this file under a single test group
//
// Note: if you use this in one file, you should use it in ALL files
//       so that each file's components are properly scoped under 1 group per file
TestGroup("My Group of Tests");

Setup { /* Setup Code */ }
Teardown { /* Teardown Code */ }

Test("Name of a test") {
  // Test code goes here...
}

Test("Name of a test") {
  // Test code goes here...
}

// Alias for Test
It("Can do something") {
  // Test code goes here...
}

// Alias for Test
Spec("Can do something else") {
  // Test code goes here...
}
```

#### Multiple Test Groups

Multiple test groups in the same file using `Describe`.

> Note: you cannot use top-level macros _inside_ a `Describe` block.

```cpp
#define spec_file MySpecs

#include <Specs.h>

Setup { /* Global Setup Code */ }

Describe("Test Group 1") {
  // Lambda Functions go here for defining setup/teardown/tests and child groups
}

Describe("Test Group 2") {
  // Lambda Functions go here for defining setup/teardown/tests and child groups
}

// Alias which takes a token instead of a string for description.
// If you only use this type of DescribeFn, then you no longer need to define spec_file.
DescribeFn(TestGroup3) {
  // Lambda Functions go here for defining setup/teardown/tests and child groups
}
```

### Lambda Functions

```cpp
#define spec_file MySpecs

#include <Specs.h>

Describe("My test group") {

  setup([]() { /* Setup Code */ });
  teardown([]() { /* Teardown Code */ });

  it("Name of a test", []() {
    // Test code goes here...
  });

  describe("Inner Group", []() {

    setup([]() { /* Setup Code */ });
    teardown([]() { /* Teardown Code */ });

    it("Name of a test", []() {
      // Test code goes here...
    });

  });
}
```

#### Without `spec_file` define

If you are using lambda functions and you want to forgo the `spec_file` define, you can do so by using the `DescribeFn` function (_alias: `TestGroup`_)

> Instead of taking a string descripteion, DescribeFn takes a token
> which is used to generate a unique name for the group.
> 
> Note: if you use any top-level macros such as Test, Setup, Teardown, etc
> then you still will need to add a #define spec_file MySpecs
> 
> But if you ONLY use the lambda functions, DescribeFn allows you to
> forgo the spec_file define.

```cpp
#include <Specs.h>

DescribeFn(MyTestGroup) {
  setup([]() { /* Setup Code */ });
  teardown([]() { /* Teardown Code */ });
  test("Name of a test", []() {
    // Test code goes here...
  });
}

// Or, you can use the TestGroupFn alias:
TestGroupFn(MyTestGroup2) {
  setup([]() { /* Setup Code */ });
  teardown([]() { /* Teardown Code */ });
  test("Name of a test", []() {
    // Test code goes here...
  });
}
```

## Command-Line Options

```
Specs.cpp command line options
Usage:
  Specs.cpp [OPTION...]

  -n, --name arg           Filter name of test/group to run
  -s, --spec arg           Filter name of test to run
  -g, --group arg          Filter name of group to run
  -r, --pattern arg        Regex pattern filter of test/group to run
      --spec-pattern arg   Regex pattern filter of test to run
      --group-pattern arg  Regex pattern filter of group to run
  -l, --list               List all tests and groups
      --dll arg            Load specs from provided .dll/.so file path
  -h, --help               Print usage
```

### Filtering Tests by Name

Running your test suite with `-n/--name something` will only run tests which contain `"something"` in the test name. This includes the spec group name(s).

To only filter on the name of the test itself, use `-s/--spec`.

To only filter on the name of the spec group, use `-g/--group`.

You can provide regex patterns to filter on names using `-r/--pattern`, `--spec-pattern`, and `--group-pattern`.

Like `-n/--name`, `-r/--pattern` will filter on both the test name and spec group name(s).

### Random Ordering

```
TODO ~ Not implemented yet
```

### Loading Tests from Shared Libraries (`.dll/.so`)

You can organize your tests into shared libraries and load them at runtime.

#### Define specs in a shared library


##### `MySpecs.cpp`

```cpp
// Instead of using <Specs/Main.h> for your console/binary entrypoint,
// for a shared library you include <Specs/DLL.h> which defines the shared library entrypoint.
#include <Specs/DLL.h>

Test("Something") {
    // Test code goes here...
}
```

Then, to load the shared library at runtime, run any Specs executable and pass the path to the shared library using `--dll` or `--so`:

```sh
MySpecs.exe --dll SomeSpecs.dll --dll SomeOtherSpecs.dll
```

## Setup and Teardown

Whenever a test is run, the following sequence of events occurs:

1. **`Setup`** code blocks are run, starting with those from the outermost group block and working inward
   - _If a setup block fails, the test execution stops and no other setups are run and the test is not run (but teardowns always are)_
2. The **`Test`** is run
3. **`Teardown`** code blocks are run, starting with those from the innermost group block and working outward
   - _If a teardown block fails, the test is marked as failed but the test execution continues and other teardowns are run_
   - _Note: if the `Setup` of the outermost group fails, then only the `Teardown` for that group will be run. `Teardown` is only run for groups for which **any** `Setup` was executed._

You can define any number of `Setup` and `Teardown` blocks at any level of nesting.

### Top-Level Setup and Teardown

```cpp
#include <Specs.h>

Setup { /* Setup Code */ }
Setup { /* More Setup Code */ }

Teardown { /* Teardown Code */ }
Teardown { /* More Teardown Code */ }

Test("Something") {
  // Test code goes here...
}
```

### Setup and Teardown inside groups

```cpp
#include <Specs.h>

Setup { /* Global Setup Code */ }
Teardown { /* Global Teardown Code */ }

Describe("Some Tests") {

  setup([]() { /* Setup Code */ });
  setup([]() { /* More Setup Code */ });

  teardown([]() { /* Teardown Code */ });
  teardown([]() { /* More Teardown Code */ });

  it("Something", []() {
    // Test code goes here...
  });

  describe("Inner Group", []() {

    setup([]() { /* Setup Code */ });
    teardown([]() { /* Teardown Code */ });

    it("Something Else", []() {
      // Test code goes here...
    });

  });
}
```

## Async Tests

`Specs.cpp` supports async tests by providing tests with a completion callback which must be called when the test is complete.

```cpp
#include <Specs.h>

// Setup and Teardown can be async
SetupAsync {
    /* Setup Code... */
    done();
}
TeardownAsync {
    /* Teardown Code... */
    done();
}

// Tests can be async
TestAsync("Something", [](SpecDone done) {
    /* Test Code... */
    done();
});
```

When tests (_and setup/teardown code blocks_) are run, if the `done()` callback is not called within the timeout period (_default: 5 seconds_), then the test is marked as failed.

You can configure the timeout via the `-t/--timeout` command-line option which takes milliseconds as an argument:

```sh
# Set timeout to 3 seconds
MySpecs.exe -t 3000
```

# Syntax

## Available Built-in Syntax

### `Test("...") { ... }`

Global top-level macro for defining tests.

These are added to the global test group (_or the test group defined by `TestGroup`, if used_).

### `TestAsync("...") { ...; done() }`

Global top-level macro for defining asyncronous tests.

These are added to the global test group (_or the test group defined by `TestGroup`, if used_).

The code block must call the `done()` callback when the test is complete.

### `TestGroup("...");`

> Alias: `SetTestGroup("...");`

Global top-level macro for defining a test group.

When used, the top-level macros `Test`, `Setup`, and `Teardown` (_etc_) will be added to this group instead of the global group.

```cpp
#include <Specs.h>

// With this, everything in this file will be scoped under a 'My Group of Tests' test group
TestGroup("My Group of Tests");

Setup {
  // Setup code goes here... (scoped to this file!)
}

Teardown {
  // Teardown code goes here... (scoped to this file!)
}

Test("Something") {
  // Test code goes here...
}
```

### `UnsetTestGroup();`

When you use `TestGroup("...")`, the defined test group is used across all files _**until**_ `TestGroup("...")` is called again with a new group.

If you would prefer to simply unset the current test group and return to the global test group, you can use `UnsetTestGroup()`.

### `Setup { ... }`

Global top-level macro for defining setup code blocks.

These are added to the global test group (_or the test group defined by `TestGroup`, if used_).

> **Note:** if you have multiple files, the `Setup` and `Teardown` blocks are shared across all files.
> 
> If you only want your `Setup` and `Teardown` to run for your specific file, please use [`TestGroup`](#testgroup) so all of your file is scoped to one test group.

### `Teardown { ... }`

Global top-level macro for defining teardown code blocks.

These are added to the global test group (_or the test group defined by `TestGroup`, if used_).

> **Note:** if you have multiple files, the `Setup` and `Teardown` blocks are shared across all files.
> 
> If you only want your `Setup` and `Teardown` to run for your specific file, please use [`TestGroup`](#testgroup) so all of your file is scoped to one test group.

### `Config { ... }`

Global top-level macro for configuring the test runner (_or anything you like!_).

This code block is executed before tests are run.

It can be used for any miscellaneous setup code.

If you use `Config` in multiple `.cpp` files, you should use `Configure` instead.

> Using `Config` in multiple `.cpp` files will result in a linker error.

### `Configure(UniqueToken) { ... }`

Global top-level macro for configuring the test runner (_or anything you like!_).

This code block is executed before tests are run.

It can be used for any miscellaneous setup code.

You must provide any kind of unique token to describe what you are configuring:

```cpp
Configure(Database) {
  // ...
}
```

> The unique token is for uniqueness across multiple `.cpp` files.

### `Describe("...") { ... }`

Global top-level macro for defining a test group.

Defines a code block in which you can define tests, setup, and teardown code blocks using functions.

Global top-level macros such as `Test`, `Setup`, and `Teardown` (_etc_) cannot be used inside this code block.

Instead, use the `test`, `setup`, and `teardown` functions.

You can also use the `describe` function to define nested groups.

### `DescribeFn(UniqueToken) { ... }`

> Alias: `TestGroupFn(UniqueToken)`

> Allows you to forgo the `spec_file` define if you only use lambda functions.

Global top-level macro for defining a test group.

Defines a code block in which you can define tests, setup, and teardown code blocks using functions.

Global top-level macros such as `Test`, `Setup`, and `Teardown` (_etc_) cannot be used inside this code block.

Instead, use the `test`, `setup`, and `teardown` functions.

You can also use the `describe` function to define nested groups.

### `test("...", []() { ... });`

> Aliases: `spec()` and `it()`

Function for defining tests inside a `Describe`/`describe` code block.

### `test("...", [](auto done) { ...; done(); });`

> Aliases: `spec()` and `it()`

Function for defining asyncronous inside a `Describe`/`describe` code block.

If you don't want to use `auto`, the full signature of the lambda is:

```cpp
// done() is a SpecDone
test("...", [](SpecDone done) { ...; done(); });
```

### `setup([]() { ... });`

Function for defining setup code blocks inside a `Describe`/`describe` code block.

### `setup([](auto done) { ...; done(); });`

Function for defining asyncronous setup code blocks inside a `Describe`/`describe` code block.

### `teardown([]() { ... });`

Function for defining teardown code blocks inside a `Describe`/`describe` code block.

### `teardown([](auto done) { ...; done(); });`

Function for defining asyncronous teardown code blocks inside a `Describe`/`describe` code block.

### `describe("...", []() { ... });`

Function for defining nested groups inside a `Describe`/`describe` code block.

## Choosing Available Syntax

By default, all of the above syntax is available.

You can pick and choose which macros and functions are available by including them directly from `<Specs/DSLs/*.h>`.

```cpp
// Do not include <Specs.h> because that includes ALL of the available DSLs
// #include <Specs.h>

// Include any of the available functions
#include <DSLs/Functions/describe.h>
#include <DSLs/Functions/test.h>
#include <DSLs/Functions/it.h> // it() { ... } is an alias for test()
#include <DSLs/Functions/spec.h> // spec() { ... } is an alias for test()
#include <DSLs/Functions/setup.h>
#include <DSLs/Functions/teardown.h>

// Include any of the available top-level macros
#include <DSLs/TopLevel/Config.h>
#include <DSLs/TopLevel/Configure.h>
#include <DSLs/TopLevel/Describe.h>
#include <DSLs/TopLevel/DescribeFn.h>
#include <DSLs/TopLevel/Setup.h>
#include <DSLs/TopLevel/SetupAsync.h>
#include <DSLs/TopLevel/Spec.h> // Spec() { ... } is an alias for Test()
#include <DSLs/TopLevel/SpecAsync.h>
#include <DSLs/TopLevel/Teardown.h>
#include <DSLs/TopLevel/TeardownAsync.h>
#include <DSLs/TopLevel/Test.h>
#include <DSLs/TopLevel/It.h> // It() { ... } is an alias for Test()
#include <DSLs/TopLevel/TestAsync.h>
#include <DSLs/TopLevel/TestGroup.h> // Alias for SetTestGroup
#include <DSLs/TopLevel/TestGroupFn.h> // Alias for DescribeFn()
#include <DSLs/TopLevel/SetTestGroup.h>
```

## Build Your Own Syntax

```
TODO - document this - Advanced Usage
``````

## Exception Handling

By default, any `std::exception` is caught and its `what()` message is used as the failure message of the test.

Also, any thrown `const char*` is caught and used as the failure message of the test.

If your test throws an exception which is not a `std::exception` or `const char*`, then the test will be marked as failed with the message `"Unknown exception"`.

If you want to catch a specific type of exception and customize the failure message, you can do so by defining a custom exception handler.

### Create Custom Exception Handler

```cpp
struct MyExceptionHandler : public SpecsCpp::IExceptionHandler {
    bool handle_exception(
        std::exception_ptr*          exception,
        IExceptionMessageCallbackFn* failureMessageCallback
    ) override {
        try {
            // Rethrow the provided exception
            std::rethrow_exception(*exception);

          // Catch your desired exception type(s) and handle them
        } catch (const custom::Exception& e) {
              // Create a custom failure message.
              // This is just a struct which wraps a string.
              SpecExceptionMessage failureMessage{e.someCustomMessageString()};

              // Incoke the callback with a pointer to the failure message.
              failureMessageCallback->invoke(&failureMessage);

            // Return true to indicate that the exception was handled
            return true;

        } catch (...) {
            // If the exception was not of the desired type, return false
            // to indicate that the exception was not handled by this handler
            return false;
        }
    }
};
```

And then register your custom handler using `Configure { ... }`:

```cpp
#include <Specs.h>
#include "MyExceptionHandler.h"

MyExceptionHandler myExceptionHandler;

Configure {
    SpecsCpp::register_exception_handler(&myExceptionHandler);
}

Test("Something") {
    throw custom::Exception("Something went wrong!");
}
```

# Spec Reporters

## Specifying reporter(s) via command-line

## Default Console Reporter

## JUnit XML Reporter

```
TODO
```

## TAP Console Reporter

```
TODO
```

## Create Custom Reporter

# Spec Runners

## Specifying runner via command-line

## Default Runner

## Parallel Runner

```
TODO
```

## Create Custom Runner

# Spec Introspection / Data Model

# TODO Wishlist

There are a few features which I hope to add in the future!

- [ ] Ability to "tag" tests (and setup/teardown/groups) with metadata
  - _For example, to customize a test's timeout or tag multiple tests with a tag that can be executed in isolation_
  - ```cpp
    #include <Specs.h>

    // Uncertain of the syntax, but here is some brainstorming:

    tag("slow")
    Test { /* ... */ }

    meta("timeout", 30000)
    Test { /* ... */ }
    ```
- [ ] Parallel test runner!
- [ ] Random order option for serial (_and later parallel_) test runner(s)
- [ ] Provide a `Print()` macro for use in tests to always show provided output
  - [ ] Consider not using `_Log_` as a dependency because many of my _tested projects_ use it
- [ ] Capture `STDOUT`/`STDERR` in tests (_and provide ways to assert on their output / output in results_)
- [ ] Host a `libassert` `vcpkg` port in the `MrowrLib/Packages` registry

# License

Use however, no attribution required.

```
BSD Zero Clause License (SPDX: 0BSD)

Permission to use, copy, modify, and/or distribute this software for any purpose
with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
THIS SOFTWARE.
```

